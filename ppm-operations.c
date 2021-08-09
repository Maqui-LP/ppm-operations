#include "ppm.h"

#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))


t_ppm ppm_operation_rotate90(t_ppm p){
  unsigned int row,col; 
  t_ppm new = ppm_create(p.width, p.height, p.depth);
  for(row=0; row < p.width; row++) for(col=0; col < p.height ; col++){
    new.pixels[row][col] = p.pixels[col][row];
  }
  return new;
}

t_ppm ppm_operation_flip_horizontal(t_ppm p){
  unsigned int row,col; 
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    new.pixels[row][col] = p.pixels[row][p.width-col-1];
  }
  return new;
}

t_ppm ppm_operation_flip_vertical(t_ppm p){
  unsigned int row,col; 
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    new.pixels[row][col] = p.pixels[p.height-row-1][col];
  }

  return new;
}

t_ppm ppm_operation_blur(t_ppm p, unsigned char ratio){
  int row, col, row_2, col_2, n, max_row, min_row, max_col, min_col;
  float av_blue, av_red, av_green;
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    min_row = MAX((row-ratio), 0);
    min_col = MAX((col-ratio), 0);
    max_row = MIN((row+ratio), p.height-1);
    max_col = MIN((col+ratio), p.width-1);
    n = 0;
    av_red = 0;
    av_green = 0;
    av_blue = 0;
    for(row_2=min_row; row_2 < max_row; row_2++) for(col_2=min_col; col_2 < max_col; col_2++){
      n++;
      av_red += p.pixels[row_2][col_2].red;
      av_green += p.pixels[row_2][col_2].green;
      av_blue += p.pixels[row_2][col_2].blue;
    }
    av_red/=n;
    av_green/=n;
    av_blue/=n;
    new.pixels[row][col].red = av_red > 255 ? 255 : (int)av_red;
    new.pixels[row][col].green = av_green > 255 ? 255 : (int)av_green;
    new.pixels[row][col].blue = av_blue > 255 ? 255 : (int)av_blue;
  }
  
  return new;

}


void ppm_invert_colours(t_ppm_pixel *p){
  p->red=255-p->red;
  p->green=255-p->green;
  p->blue=255-p->blue;
}

t_ppm ppm_operation_negative(t_ppm p){
  unsigned int row,col; 
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for(row=0; row < p.height; row++) for(col=0; col < p.width ; col++){
    new.pixels[row][col] = p.pixels[row][col];
    ppm_invert_colours(&new.pixels[row][col]);
  }
  return new;
}

