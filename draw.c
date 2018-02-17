#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z
Returns:
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  if (points->lastcol == points->cols){
    grow_matrix(points, (points->cols)*10);
  }

  points->lastcol++;

  int column = (points->lastcol) - 1;
  points->m[0][column] = x;
  points->m[1][column] = y;
  points->m[2][column] = z;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns:
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points,
	       double x0, double y0, double z0,
	       double x1, double y1, double z1) {
           add_point(points, x0, y0, z0);
           add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c
Returns:
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
  int i;
  for (i = 0; i < points->lastcol; i+=2){
    draw_line(points->m[0][i], points->m[1][i], points->m[0][i+1], points->m[1][i+1], s, c);
    printf("point 1: %f, %f\n", points->m[0][i], points->m[1][i]);
    printf("point 2: %f, %f\n", points->m[0][i+1], points->m[1][i+1]);
  }
}

void draw_line(int x0, int y0, int x1, int y1, screen s, color c){
  if (x0 > x1){ // swaps right to left lines so I only need to do 4 octants
      int x_holder = x1;
      int y_holder = y1;
      x1 = x0;
      y1 = y0;
      x0 = x_holder;
      y0 = y_holder;
  }

  int A = y1 - y0;
  int B = x0 - x1;

  int x = x0;
  int y = y0;
  int d;
  float slope = 1.0 * (y1 - y0)/(x1 - x0);
  if (slope <= 1 && slope >= 0){ //octant 1
      d = 2*A + B;
      while (x <= x1){
          plot(s, c, x, y);
          if (d > 0){
              y++;
              d += 2*B;
          }
          x++;
          d += 2*A;
      }
  }
  else if (slope > 1 && slope <= INFINITY){ // octant 2
      d = A + 2*B;
      while (y <= y1){
          plot(s, c, x, y);
          if (d < 0){
              x++;
              d += 2*A;
          }
          y++;
          d += 2*B;
      }
  }
  else if (slope < 0 && slope >= -1){ // octant 8
      d = 2*A-B;
      while (x <= x1){
          plot(s, c, x, y);
          if (d < 0){
              y--;
              d -= 2*B;
          }
          x++;
          d += 2*A;
      }
  }
  else if (slope < -1 && slope >= -INFINITY){ // octant 7
      d = A - 2*B;
      while (y >= y1){
          plot(s, c, x, y);
          if (d > 0){
              x++;
              d += 2*A;
          }
          y--;
          d -= 2*B;
      }
  }
}
