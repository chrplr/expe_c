/* tokenize a text file
 * 
 *
 * Time-stamp: <2021-07-02 10:26:26 christophe@pallier.org>
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <search.h>


const char* DELIMITERS = "!\"#$%&'()*+,-./:;<=>?@[]^_`{|}~\\\t\n\r ";

void replace_nonalphanum_by_spaces(char *str)
/* TODO: currently only handle ASCII! It should handle UTF-8 input and locale */
{
        for (unsigned long i = 0; i < strlen(str); i++) {
                if (!isalnum(str[i]))
                        str[i] = ' ';
        }
}

int main(int argc, char* argv[])
{
        FILE* fd;
        char* line = NULL;
        size_t len = 0;
        ssize_t nread;

        fd = (argc > 1)? fopen(argv[1],"r") : stdin;
        if (!fd)
        {
                fprintf(stderr, "Error opening file '%s'\n", argv[1]);
                return EXIT_FAILURE;
        }

        while ((nread = getline(&line, &len, fd)) != -1) {
                //replace_nonalphanum_by_spaces(line);
                char* token = strtok(line, DELIMITERS);
                while (token != NULL) {
                        puts(token);
                        token = strtok(NULL, DELIMITERS);
                }
        }

        free(line);

        return 0;
}
