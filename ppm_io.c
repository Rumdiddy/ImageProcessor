//Samuel Jin
//Ajay Ananthakrishnan
//sjin16
//aananth3

// ppm_io.c
// 601.220, Spring 2019

#include <assert.h>
#include "ppm_io.h"
#include <string.h>
#include <stdio.h>


/* Read a PPM-formatted image from a file (assumes fp != NULL).
 * Returns the address of the heap-allocated Image struct it
 * creates and populates with the Image data.
 */
Image * read_ppm(FILE *fp) {
  assert(fp); 
  int col;
  int row;
  char *magic;
  int colors;

  fscanf(fp, "%s %i %i %i", magic, col, row, colors);
  assert(strlen(magic) == 2);
  assert(magic[1] == '6' && magic[0] = 'P');
  assert(colors == 255);

  Image *input;
  *input.rows = row;
  *input.cols = col;
  int size = row * col;

  Pixel *dat = malloc(size * sizeof(Pixel));
  fread(dat, sizeof(Pixel), size, fp);
   
  return input;  
}


/* Write a PPM-formatted image to a file (assumes fp != NULL),
 * and return the number of pixels successfully written.
 */
int write_ppm(FILE *fp, const Image *im) {

  // check that fp is not NULL
  assert(fp); 

  // write PPM file header, in the following format
  // P6
  // cols rows
  // 255
  fprintf(fp, "P6\n%d %d\n255\n", im->cols, im->rows);

  // now write the pixel array
  int num_pixels_written = fwrite(im->data, sizeof(Pixel), im->cols * im->rows, fp);

  if (num_pixels_written != im->cols * im->rows) {
    fprintf(stderr, "Uh oh. Pixel data failed to write properly!\n");
  }

  return num_pixels_written;
}

