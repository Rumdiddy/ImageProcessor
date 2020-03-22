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

/* Checks the command line arguments and operation and ensures
 * that the correct arguments are provided.
 */
int arg_check(int argc, char *argv[]) {
  //Checks for correct number of arguments
  switch (argc) {
    case 1: 
      printf("Failed to supply input filename, output filename, and operation name.\n");
      return 1;
    case 2:
      printf("Failed to supply output filename and operation name.\n");
      return 1;
    case 3:
      printf("No operation name was specified.\n");
      return 4;
  }

  //Checks for the operation name
  int oper;
  if (strcmp(argv[3], "exposure") == 0) {
    oper = 1;
  } else if (strcmp(argv[3], "blend") == 0) {
    oper = 2;
  } else if (strcmp(argv[3], "zoom_in") == 0) {
    oper = 3;
  } else if (strcmp(argv[3], "zoom_out") == 0) {
    oper = 4;
  } else if (strcmp(argv[3], "pointilism") == 0) {
    oper = 5;
  } else if (strcmp(argv[3], "swirl") == 0) {
    oper = 6;
  } else if (strcmp(argv[3], "blur") == 0) {
    oper = 7;
  } else {
    printf("Operation name specified was invalid.\n");
    return 4;
  }

  //Check for correct operation arguments
  switch (oper) {
    case 1: //exposure
      if (strtof(argv[4], NULL) == 0.0F && *argv[4] != 48) {
        printf("Argument for specified operation were senseless.\n");
        return 6;
      } else if (strtof(argv[4], NULL) > 3 || strtof(argv[4], NULL) < -3) {
        printf("Arguments for specified operation were out of range.\n");
        return 6;
      } else if (argc > 5) {
        printf("Incorrect number of arguments for specified operation.\n");
        return 5;
      }
      break;
    case 2: //blend 
      if (argc > 6) {
        printf("Incorrect number of arguments for specified operation.\n");
        return 5;
      } else if (strtof(argv[5], NULL) == 0.0F && *argv[5] != 48) {
        printf("Argument for specified operation were senseless.\n");
        return 6;
      } else if (strtof(argv[5], NULL) > 1 || strtof(argv[5], NULL) < 0) {
        printf("Arguments for specified operation were out of range.\n");
        return 6;
      }
      FILE* i2fptr = fopen(argv[4], "r");
      if (i2fptr == NULL) {
        printf("Specified input file could not be opened.\n");
        return 2;
      }
      break;
    case 3: //zoom_in
      if (argc > 4) {
        printf("Incorrect number of arguments for specified operation.\n");
        return 5;
      }
      break;
    case 4: //zoom_out
      if (argc >4) {
        printf("Incorrect number of arguments for specified operation.\n");
        return 5;
      }
  }
  return 0;
}
