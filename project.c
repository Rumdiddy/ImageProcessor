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
    
  //Generates empty output image to write into
  Image * outputIm = gen_out(opval, inputIm, inputIm2);

  //TO DO: run function here based on opval
    
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
  //  free(outputIm);
   
  return 0;
}

