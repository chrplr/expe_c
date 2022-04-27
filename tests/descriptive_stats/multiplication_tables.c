/* multiplication tables */

/* From Klemens, Ben. 2009. Modeling with Data: Tools and Techniques for Scientific Computing. Princetin University Press. */

#include <apop.h>

int main()
{
     gsl_matrix *m = gsl_matrix_alloc(20, 15);
     gsl_matrix_set_all(m, 1);

     for (int i = 0; i < (m -> size1); i++){
          Apop_matrix_row(m, i, one_row);
          gsl_vector_scale(one_row, i+1);
     }

     for (int i = 0; i < (m -> size2); i++){
          Apop_matrix_col(m, i, one_col);
          gsl_vector_scale(one_col, i+1);
     }

     apop_matrix_show(m);
     gsl_matrix_free(m);
}
