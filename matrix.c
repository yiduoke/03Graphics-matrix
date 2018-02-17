#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m
Returns:

print the matrix
*/
void print_matrix(struct matrix *m) {
  int i;
  for (i = 0; i < m->rows; i++){
    int j;
    for (j = 0; j < m->lastcol; j++){
      printf("%d  ", (int)m->m[i][j]);
    }
    printf("\n");
  }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns:

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int i;
  m->lastcol = m->rows;
  for (i = 0; i < m->rows; i++){
    int j;
    for (j = 0; j < m->cols; j++){
      if (i == j){
        m->m[i][j] = 1;
      }
      else{
        m->m[i][j] = 0;
      }
    }
  }
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b
Returns:

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  if (a->lastcol != b->rows){
    printf("can't multiply this\n");
    return;
  }
  struct matrix* output = new_matrix(a->rows, b->lastcol);

  int i;
  for (i = 0; i < a->rows; i++){
    int j;
    for (j = 0; j < b->lastcol; j++){
      int inner;
      float product = 0;
      for (inner = 0; inner < a->lastcol; inner++){
        product += a->m[i][inner] * b->m[inner][j];
      }
      output->m[i][j] = product;
    }
  }
  copy_matrix(output, b);
}

/*===============================================
  These Functions do not need to be modified
  ===============================================*/

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols
Returns:

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)...
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m
Returns:

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols
Returns:

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {

  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b
Returns:

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++)
    for (c=0; c < a->cols; c++)
      b->m[r][c] = a->m[r][c];
}
