#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
  struct matrix *edges;
  struct matrix* trans;

  edges = new_matrix(4, 4);
  trans = new_matrix(4, 4);
  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = MAX_COLOR;

  ident(trans);
  printf("should be an identity matrix\n");
  print_matrix(trans); // should be identity matrix

  add_edge(edges, 100, 100, 0, 400, 100, 0);
  add_edge(edges, 400, 100, 0, 250, 350, 0);
  add_edge(edges, 250, 350, 0, 100, 100, 0);

  matrix_mult(trans, edges);

  printf("\nshould be edges itself: \n");
  print_matrix(edges); // should be edges itself

  trans->m[0][3] = 50; //dx = +100
  trans->m[1][3] = -50; //dx = +100
  printf("\nnew trans (translation):\n");
  print_matrix(trans);

  matrix_mult(trans, edges);
  printf("\nnew edges:\n");
  print_matrix(edges);

  draw_lines(edges, s, c);
  display(s);
  save_extension(s, "matrix.png");
  free_matrix( edges );
}
