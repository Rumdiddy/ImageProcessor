//Samuel Jin
//Ajay Ananthakrishnan
//sjin16
//aananth3

//project.c

#include "imageManip.h"
#include "ppm_io.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {

  //Checks command line arguments + operation
  int opval = arg_check(argc, argv);
  if (opval < 11) {
    return opval;
  }
  
  //Opens input file for reading
  FILE* ifptr;
  ifptr = fopen(argv[1], "rb");

  if (ifptr == NULL) {
    printf("Specified input file could not be opened.\n");
    return 2;
  }

    //Opens or creates output file for writing
  FILE* ofptr;
  ofptr = fopen(argv[2], "wb");

  if (ofptr == NULL) {
    printf("Output file could not be opened.\n");
    return 7;
  }

  Image * inputIm2 = malloc(sizeof(Image));
  //Check if blend is operation and will read in second input file
  if (opval == 12) {
    FILE* i2fptr = fopen(argv[4], "rb");
    if (i2fptr == NULL) {
      printf("Specified input file could not be opened.\n");
      return 2;
    }
    inputIm2 = read_ppm(i2fptr);
    fclose(i2fptr);
  }

  //Reads in input file pixel data and generates image
  Image * inputIm = read_ppm(ifptr);
  if(((*inputIm).rows == -1) && ((*inputIm2).rows == -1)) {
    printf("Specified input file is not a properly-formatted PPM.");
    return 3;
  }
  fclose(ifptr);

  //Further checks arguments provided for swirl
  int cx;
  int cy;
  int strength;
  if (opval == 16) {
    if (atoi(argv[4]) < 0 || atoi(argv[4]) > (inputIm->cols)) {
      printf("Arguments for specified operation were out of range.\n");
      return 6;
    } else if (atoi(argv[5]) < 0 || atoi(argv[5]) > (inputIm->rows)) {
      printf("Arguments for specified operation were out of range.\n");
      return 6;
    } else {
      cx = atoi(argv[4]);
      cy = atoi(argv[5]);
      strength = atoi(argv[6]);
    }
  }

  //Generates factor for functions
  double factor;
  switch (opval) {
  case 11:
    factor = strtof(argv[4], NULL);
    break;
  case 12:
    factor = strtof(argv[5], NULL);
    break;
  case 17:
    factor = strtod(argv[4], NULL);
    break;
  }
    
  //Generates empty output image to write into
  Image * outputIm = gen_out(opval, inputIm, inputIm2);

  //Run function here based on opval
  frun(opval, inputIm, inputIm2, outputIm, factor);
  if (opval == 16) { //swirl
    swirl(inputIm, outputIm, cx, cy, strength);
  }
  
  /*Writing output to file
   *Pointilism changes the input array passed into it.
   */
  int outval;
  if (opval == 15 || opval == 11) {
    outval = write_ppm(ofptr, inputIm);
  } else {
    outval = write_ppm(ofptr, outputIm);
  }

  if (outval == -1) {
    printf("Writing output to file failed or invalid. \n");
    return 7;
  }
  
  free(inputIm);
  free(inputIm2);
  free(outputIm);
   
  return 0;
}

