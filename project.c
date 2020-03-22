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
  int argval = arg_check(argc, argv);
  if (argval != 0) {
    return argval;
  }
  
  //Opens input file for reading
  FILE* ifptr;
  ifptr = fopen(argv[1], "r");

  if (ifptr == NULL) {
    printf("Specified input file could not be opened.\n");
    return 2;
  }

  Image * inputIm = read_ppm(ifptr);

  
  return 0;
}

