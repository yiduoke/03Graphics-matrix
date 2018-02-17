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

  edges = new_matrix(4, 4);
  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = MAX_COLOR;
  //
  add_edge(edges, 300, 400, 0, 300, 0, 0);
  // print_matrix(edges);

  draw_lines(edges, s, c);
  display(s);
  save_extension(s, "matrix.png");
  free_matrix( edges );
}
