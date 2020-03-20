//Samuel Jin
//Ajay Ananthakrishnan
//sjin16
//aananth3

//imageManip.c
//Implementation of the operation functions in imageManip.h

#include "imageManip.h"


void exposure(Image *input, Image *output, double factor){

  inputLength = (*input -> rows) * (*input -> cols); 
  for (int i = 0; i < inputLength; i++){
    *(output -> data + i) = *(input -> data + i) * pow(2, factor); 
  }
}


void zoomIN(Image *input, Image *output){

  inputLength =	(*input -> rows) * (*input -> cols);
  
  for (int i = 0; i < inputLength; i++){
    
    for (int j = 0; j < 4; j++){

      if (i>1){
        *(output -> data + i + (*input ->rows) +j - 2) = *(input -> data + i);
      }
      else{
      *(output -> data + i +j) = *(input -> data + i);
      }
    }
  }

}
