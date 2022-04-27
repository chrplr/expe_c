#include "vector.h"

void init_vector(vector *vec, size_t initialSize)
{
     vec->data = malloc(initialSize * sizeof(double));
     assert (vec->data);
     vec->size = 0;
     vec->allocated = initialSize;
}

void push_back_vector(vector *vec, double element)
{
  if (vec->size == vec->allocated) {
    size_t wanted = vec->allocated * 2;
    double *new_data = realloc(vec->data, wanted * sizeof(double));
    assert (new_data);
    vec->data = new_data;
  }

  vec->data[vec->size++] = element;
}


void free_vector(vector vec)
{
  free(vec.data);
  vec.data = NULL;
  vec.allocated = vec.size = 0;
}


void print_vector(vector vec, char *format, char *sep)
{
        for (uint i = 0; i < vec.size; i++) {
                printf(format, vec.data[i]);
                if (i < (vec.size - 1))
                     printf("%s", sep);
        }
        printf("\n");
}

void read_vector(vector *vec, FILE *stream)
{
        char* line = NULL;
        size_t len = 0;
        ssize_t nread;

        const char* DELIMITERS = "!\"#$%&'()*+,-./:;<=>?@[]^_`{|}~\\\t\n\r ";

        while ((nread = getline(&line, &len, stream)) != -1) {
                char* token = strtok(line, DELIMITERS);
                while (token != NULL) {
                        double x = strtod(token, NULL);
                        push_back_vector(vec, x);
                        token = strtok(NULL, DELIMITERS);
                }
        }

        free(line);

}


