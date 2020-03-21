//Samuel Jin
//Ajay Ananthakrishnan
//sjin16
//aananth3

//project.c

#include "imageManip.h"
#include "ppm_io.h"
#include <assert.h>
#include <string.h>

int main (int argc, char *argv[]) {

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

