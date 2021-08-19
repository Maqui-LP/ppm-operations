#include "ppm.h"

#define MAX_COLOR_VALUE (255)
#define BLACK_AND_WHITE_THRESHOLD (128)
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

t_ppm ppm_operation_rotate90(t_ppm p)
{
  unsigned int row, col;
  t_ppm new = ppm_create(p.width, p.height, p.depth);
  for (row = 0; row < p.width; row++)
    for (col = 0; col < p.height; col++)
    {
      new.pixels[row][col] = p.pixels[col][row];
    }
  return new;
}

t_ppm ppm_operation_flip_horizontal(t_ppm p)
{
  unsigned int row, col;
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for (row = 0; row < p.height; row++)
    for (col = 0; col < p.width; col++)
    {
      new.pixels[row][col] = p.pixels[row][p.width - col - 1];
    }
  return new;
}

t_ppm ppm_operation_flip_vertical(t_ppm p)
{
  unsigned int row, col;
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for (row = 0; row < p.height; row++)
    for (col = 0; col < p.width; col++)
    {
      new.pixels[row][col] = p.pixels[p.height - row - 1][col];
    }

  return new;
}

t_ppm ppm_operation_blur(t_ppm p, unsigned char ratio)
{
  int row, col, row_2, col_2, n, max_row, min_row, max_col, min_col;
  float av_blue, av_red, av_green;
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for (row = 0; row < p.height; row++)
    for (col = 0; col < p.width; col++)
    {
      min_row = MAX((row - ratio), 0);
      min_col = MAX((col - ratio), 0);
      max_row = MIN((row + ratio), p.height - 1);
      max_col = MIN((col + ratio), p.width - 1);
      n = 0;
      av_red = 0;
      av_green = 0;
      av_blue = 0;
      for (row_2 = min_row; row_2 < max_row; row_2++)
        for (col_2 = min_col; col_2 < max_col; col_2++)
        {
          n++;
          av_red += p.pixels[row_2][col_2].red;
          av_green += p.pixels[row_2][col_2].green;
          av_blue += p.pixels[row_2][col_2].blue;
        }
      av_red /= n;
      av_green /= n;
      av_blue /= n;
      new.pixels[row][col].red = av_red > MAX_COLOR_VALUE ? MAX_COLOR_VALUE : (int)av_red;
      new.pixels[row][col].green = av_green > MAX_COLOR_VALUE ? MAX_COLOR_VALUE : (int)av_green;
      new.pixels[row][col].blue = av_blue > MAX_COLOR_VALUE ? MAX_COLOR_VALUE : (int)av_blue;
    }

  return new;
}

void ppm_invert_colours(t_ppm_pixel *p)
{
  p->red = MAX_COLOR_VALUE - p->red;
  p->green = MAX_COLOR_VALUE - p->green;
  p->blue = MAX_COLOR_VALUE - p->blue;
}

t_ppm ppm_operation_negative(t_ppm p)
{
  unsigned int row, col;
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for (row = 0; row < p.height; row++)
    for (col = 0; col < p.width; col++)
    {
      new.pixels[row][col] = p.pixels[row][col];
      ppm_invert_colours(&new.pixels[row][col]);
    }
  return new;
}

void ppm_apply_sepia(t_ppm_pixel *p)
{

  // conversion formula from rgb to sepia
  float r = (p->red * 0.393) + (p->green * 0.769) + (p->blue * 0.189);
  float g = (p->red * 0.349) + (p->green * 0.686) + (p->blue * 0.168);
  float b = (p->red * 0.272) + (p->green * 0.534) + (p->blue * 0.131);

  p->red = r > MAX_COLOR_VALUE ? MAX_COLOR_VALUE : (unsigned char)r;
  p->green = g > MAX_COLOR_VALUE ? MAX_COLOR_VALUE : (unsigned char)g;
  p->blue = b > MAX_COLOR_VALUE ? MAX_COLOR_VALUE : (unsigned char)b;
}

t_ppm ppm_operation_sepia(t_ppm p)
{
  unsigned int row, col;
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for (row = 0; row < p.height; row++)
    for (col = 0; col < p.width; col++)
    {
      new.pixels[row][col] = p.pixels[row][col];
      ppm_apply_sepia(&new.pixels[row][col]);
    }
  return new;
}

void ppm_apply_grayscale(t_ppm_pixel *p)
{
  // conversion formula from rgb to grayscale
  float grayscale = (p->red * 0.3) + (p->green * 0.3) + (p->blue * 0.3);
  grayscale = grayscale > MAX_COLOR_VALUE ? MAX_COLOR_VALUE : (unsigned char)grayscale;

  p->red = grayscale;
  p->green = grayscale;
  p->blue = grayscale;
}

t_ppm ppm_operation_grayscale(t_ppm p)
{
  unsigned int row, col;
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for (row = 0; row < p.height; row++)
    for (col = 0; col < p.width; col++)
    {
      new.pixels[row][col] = p.pixels[row][col];
      ppm_apply_grayscale(&new.pixels[row][col]);
    }
  return new;
}

void ppm_apply_bw(t_ppm_pixel *p)
{
  float grayscale = (p->red * 0.3) + (p->green * 0.3) + (p->blue * 0.3);
  unsigned char black_or_white = grayscale > BLACK_AND_WHITE_THRESHOLD ? MAX_COLOR_VALUE : 0;

  p->red = black_or_white;
  p->green = black_or_white;
  p->blue = black_or_white;
}

t_ppm ppm_operation_black_and_white(t_ppm p)
{
  unsigned int row, col;
  t_ppm new = ppm_create(p.height, p.width, p.depth);
  for (row = 0; row < p.height; row++)
    for (col = 0; col < p.width; col++)
    {
      new.pixels[row][col] = p.pixels[row][col];
      ppm_apply_bw(&new.pixels[row][col]);
    }
  return new;
}
