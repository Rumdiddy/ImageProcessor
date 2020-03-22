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
  ifptr = fopen(argv[1], "r");

  if (ifptr == NULL) {
    printf("Specified input file could not be opened.\n");
    return 2;
  }

  //Check if blend is operation and will read in second input file
  if (opval == 12) {
    FILE* i2fptr = fopen(argv[4], "r");
    if (i2fptr == NULL) {
      printf("Specified input file could not be opened.\n");
      return 2;
    }

    Image * inputIm2 = read_ppm(i2fptr);
  }

  //Reads in input file pixel data and generates image
  Image * inputIm = read_ppm(ifptr);
  if((*inputIm.rows == -1) && (*inputIm2.rows == -1)) {
    printf("Specified input file is not a properly-formatted PPM.");
    return 3;
  }
  
  return 0;
}

