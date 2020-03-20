//Samuel Jin
//Ajay Ananthakrishnan
//sjin16
//aananth3

//imageManip.c
//Implementation of the operation functions in imageManip.h

#include "imageManip.h"

//implementation of the exposure function which modifies the exposure of the input image 
//and writes the altered pixel values to the output.
void exposure(Image *input, Image *output, double factor){

  inputLength = (*input.rows) * (*input.cols); 
  for (int i = 0; i < inputLength; i++){
    *(output -> data + i) = *(input -> data + i) * pow(2, factor); 
  }
}

//implementation of the zoomin function which zooms in on the input image by a factor of 2
//and produces an output image 4 times the area.
void zoomIN(Image *input, Image *output){

  inputLength =	(*input.rows) * (*input.cols);
  
  int outind = 0;
  int rowskip = 0;
  
  //Iterates through the output and input image.
  for (int i = 0; i < inputLength; i++){ 
   
   for (int j = 0; j < 4; j++){
    
      if (j > 1){
        *(output -> data + (rowskip * (*input.cols)) + (2 * i) + (*input.cols) + (j - 2)) = *(input -> data + i);
      }
      else{
      *(output -> data + (rowskip * (*input.cols)) + (2 * i) +j) = *(input -> data + i);
      }
    }
    
    //allows for the second row to be skipped each time
    if ((i % (*input.cols)) == ((*input.cols) - 1)) {
      rowskip++;
    }
  }
}
