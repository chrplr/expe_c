/* read and write parameters from a file (in [toml format](https://toml.io/en/))
 * using locks as an external process can alter the parameters
 *
 */

/* -*- mode:c; c-default-style: linux  -*- Time-stamp: <2021-06-24 12:29:34 christophe@pallier.org> */

#define _GNU_SOURCE //cause stdio.h to include asprintf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <toml.h> /* https://github.com/cktan/tomlc99 */

#define PARAMS_FILE "params.toml"

/* Example of param file:
 * square_length = 200
 * square_color = 0xFFFFFFFFF
 * circle_radius = 50
 * circle_color = 0x0000000FF
 * background_color = 0xFFFFFFFFF
 */


typedef struct parameters {
     int square_length;
     int square_color;
     int circle_radius;
     int circle_color;
     int background_color;
} parameters;


void params_to_toml(struct parameters p, char** buf)
{
     asprintf(buf, "square_length = %d\nsquare_color=0x%X\ncircle_radius=%d\ncircle_color=0x%X\nbackground_color=0x%X",
              p.square_length,
              p.square_color,
              p.circle_radius,
              p.circle_color,
              p.background_color);
}


static void error(const char* msg, const char* msg1)
{
        fprintf(stderr, "ERROR: %s%s\n", msg, msg1?msg1:"");
        exit(1);
}


void write_parameters(struct parameters p, char* toml_file)
{
     char *buf;
     params_to_toml(p, &buf);

     struct flock lock = {
          .l_type = F_WRLCK,
          .l_whence = SEEK_SET,
          .l_start = 0,
          .l_len = 0,
          .l_pid = getpid()
     };

     int fd;
     if ((fd = open(toml_file, O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0)
          error("open failed...", strerror(errno));

     if (fcntl(fd, F_SETLKW, &lock) < 0)
          error("fcntl failed to get lock...", strerror(errno));
     else
          write(fd, buf, strlen(buf));

     lock.l_type = F_UNLCK;
     if (fcntl(fd, F_SETLK, &lock) < 0)
          error("unlocking failed...", strerror(errno));
     close(fd);
     free(buf);
}

struct parameters read_parameters(char* toml_file)
{
    FILE* fp;
    char errbuf[200];

    struct flock lock = {
            lock.l_type = F_WRLCK,
            lock.l_whence = SEEK_SET,
            lock.l_start = 0,
            lock.l_len = 0,
            lock.l_pid = getpid()
    };

    fp = fopen(toml_file, "r");
    if (!fp) {
        error("cannot open file ", strerror(errno));
    }

    // Wait until the file is not locked (risk of infinite loop if the lock is not released)
    do {
            fcntl(fileno(fp), F_GETLK, &lock);
            usleep(10);
    }
    while (lock.l_type != F_UNLCK);

    // prevents any writing during the reading
    lock.l_type = F_RDLCK;
    if (fcntl(fileno(fp), F_SETLK, &lock) < 0)
            error("can't get a read-only lock...", strerror(errno));

    toml_table_t* param_table = toml_parse_file(fp, errbuf, sizeof(errbuf));

    // Release the lock
    lock.l_type = F_UNLCK;
    if (fcntl(fileno(fp), F_SETLK, &lock) < 0)
            error("cannot unlock", strerror(errno));

    fclose(fp);

    if (!param_table) {
        error("cannot parse - ", errbuf);
    }

    toml_datum_t p1 = toml_int_in(param_table, "square_length");
    if (!p1.ok)
         error("malformed p1 - ", errbuf);

    toml_datum_t p2 = toml_int_in(param_table, "square_color");

    if (!p2.ok)
         error("malformed p2 - ", errbuf);

    toml_datum_t p3 = toml_int_in(param_table, "circle_radius");
    if (!p3.ok)
         error("malformed p3 - ", errbuf);

    toml_datum_t p4 = toml_int_in(param_table, "circle_color");
    if (!p4.ok)
         error("malformed p4 - ", errbuf);

    toml_datum_t p5 = toml_int_in(param_table, "background_color");
    if (!p5.ok)
         error("malformed p5 - ", errbuf);

    /* if (!p1.ok || !p2.ok || !p3.ok || !p4.ok || !p5.ok) { */
    /*         error("malformed parameter file - ", errbuf); */
    /* } */

    struct parameters params = {
            .square_length = (int)p1.u.i,
            .square_color = (int)p2.u.i,
            .circle_radius = (int)p3.u.i,
            .circle_color = (int)p4.u.i,
            .background_color = (int)p5.u.i
    };

    return params;
}


int is_file_modified(char* fname)
{
     static struct statx statxbuf;
     static struct statx_timestamp ts0 = {0, 0, 0}, ts1;
     int modified = 0;

     statx(AT_FDCWD, fname, 0, STATX_MTIME, &statxbuf);
     ts1 = statxbuf.stx_mtime;

     if (ts0.tv_sec == 0 && ts0.tv_nsec == 0)   // first passage
          modified = 1;
     else
          modified = ((ts1.tv_sec != ts0.tv_sec) || (ts1.tv_nsec != ts0.tv_nsec));

     ts0.tv_sec = ts1.tv_sec;
     ts0.tv_nsec = ts1.tv_nsec;

     return modified;
}

int main()
{
     struct parameters params = {
          .square_length = 1,
          .square_color = 1,
          .circle_radius = 1 ,
          .circle_color = 1,
          .background_color = 1
     };

     printf("starting... ");
     for (int i=0; i < 60; i++)
     {
          printf("\n%d:\n ", i);
          char *buf;
          params_to_toml(params, &buf);
          puts(buf);
          free(buf);

          write_parameters(params, PARAMS_FILE);
          params.square_length++;
          sleep(1);
     }

     return 0;
}
