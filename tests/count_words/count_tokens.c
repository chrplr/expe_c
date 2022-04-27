/* tokenize a text file
 * 
 *
 * Time-stamp: <2021-07-04 14:56:23 christophe@pallier.org>
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <search.h>

#include "utarray.h"

const char* DELIMITERS = "!\"#$%&'()*+,-./:;<=>?@[]^_`{|}~\\\t\n\r ";

static int strsort(const void *_a, const void *_b)
{
    const char *a = *(const char* const *)_a;
    const char *b = *(const char* const *)_b;
    return strcmp(a, b);
}


uthash count_items(utarray);
{

}

int main(int argc, char* argv[])
{
        FILE* fd;
        char* line = NULL;
        size_t len = 0;
        ssize_t nread;

        UT_array *strs = NULL;
        utarray_new(strs, &ut_str_icd);



        fd = (argc > 1)? fopen(argv[1],"r") : stdin;
        if (!fd)
        {
                fprintf(stderr, "Error opening file '%s'\n", argv[1]);
                return EXIT_FAILURE;
        }

        while ((nread = getline(&line, &len, fd)) != -1) {
                char* token = strtok(line, DELIMITERS);
                while (token != NULL) {
                        utarray_push_back(strs, &token);
                        token = strtok(NULL, DELIMITERS);
                }
        }

        utarray_sort(strs, strsort);

        char **p = NULL;
        while ( (p=(char**)utarray_next(strs,p))) {
             printf("%s\n",*p);
        }

        /* char *s;  */
        /* int rep = 0; */
        /* while ((p = (char**)utarray_next(strs, p))) { */
        /*         printf("%s\n", *p); */
        /*         if (!s && !strcmp(*p, s)) */
        /*                 rep++; */
        /*         else { */
        /*                 printf("%s\t%d\n", s, rep); */
        /*                 rep = 0; */
        /*                 s = *p; */
        /*         } */
        /* } */

        free(line);

        utarray_free(strs);

        return 0;
}
