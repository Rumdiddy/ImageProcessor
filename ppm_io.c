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
#include <stdlib.h>

/* Read a PPM-formatted image from a file (assumes fp != NULL).
 * Returns the address of the heap-allocated Image struct it
 * creates and populates with the Image data.
 */
Image * read_ppm(FILE *fp) {
  assert(fp); 
  int col;
  int row;
  char magic[3];
  int colors;
  Image * input = malloc(sizeof(Image));

  
  //Skips over comment lines or new lines until EOF
  /* char n = '#'; */
  /* while (n == '#') { */
  /*   n = fgetc(fp); */
  /*   while (n != '\n' && n!= EOF) { */
  /*   } */
  /* } */
  /* ungetc(n, fp); */

  
  //Checks if PPM file is properly formatted
  fscanf(fp, "%s %i %i %i", magic, &col, &row, &colors);
  if(strlen(magic) != 2) {
    (*input).rows = -1;
    return input;
  } else if (magic[1] != '6' || magic[0] != 'P') {
    (*input).rows = -1;
    return input;
  } else if (colors != 255) {
    (*input).rows = -1;
    return input;
  }

  //sets rows and columns
  (*input).rows = row;
  (*input).cols = col;
  int size = row * col;
  
  //Reads in pixel data
  
  (*input).data = malloc(size * sizeof(Pixel));
  char c = fgetc(fp);

  fread((*input).data, sizeof(Pixel), size, fp);
  
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
    return -1;
  }

  return num_pixels_written;
}

/* Checks the command line arguments and operation and ensures
 * that the correct arguments are provided. Returns operation value.
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
    oper = 11;
  } else if (strcmp(argv[3], "blend") == 0) {
    oper = 12;
  } else if (strcmp(argv[3], "zoom_in") == 0) {
    oper = 13;
  } else if (strcmp(argv[3], "zoom_out") == 0) {
    oper = 14;
  } else if (strcmp(argv[3], "pointilism") == 0) {
    oper = 15;
  } else if (strcmp(argv[3], "swirl") == 0) {
    oper = 16;
  } else if (strcmp(argv[3], "blur") == 0) {
    oper = 17;
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
  return oper;
}

//Checks if the rgb values overflow past 255;
unsigned char overflowcheck(double rgb) {
  if (rgb > 255 || rgb < 0) {
    return 255;
  } else {
    return (unsigned char)rgb;
  }
}


/* Generates output image to be filled. It determines
 * the output image size based on the operation specified.
 */
Image * gen_out(int oper, Image *input1, Image *input2) {
  int rows1 = (*input1).rows;
  int cols1 = (*input1).cols;
  int size1 = rows1 * cols1;

  int rows2 = (*input2).rows;
  int cols2 = (*input2).cols;

  Image *output = malloc(sizeof(Image));
  int osize;

  switch (oper) {
    case 12:  //blend
      //checks for largest rows
      if (rows1 > rows2) {
        (*output).rows = rows1;
      } else {
        (*output).rows = rows2;
      }

      //checks for largest columns
      if (cols1 > cols2) {
        (*output).cols = cols1;
      } else {
        (*output).cols = cols2;
      }

      osize = (*output).cols * (*output).rows;
      (*output).data = malloc(osize * sizeof(Pixel));
      break;
    case 13:  //zoom_in
      (*output).data = malloc(4 * size1 * sizeof(Pixel));
      (*output).rows = (2 * rows1);
      (*output).cols = (2 * cols1);
      break;
    case 14:  //zoom_out
      (*output).data = malloc((1.0/4.0) * size1 * sizeof(Pixel));
      (*output).rows = (0.5 * rows1);
      (*output).cols = (0.5 * cols1);
      break;
    case 15:  //pointilism modifies input image
      break;
    case 16:  //swirl
      //TO-DO
      break;
    case 17:  //blur
      //TO-DO
      break;
  }  
  return output;
}
