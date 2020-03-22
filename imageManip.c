
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

  int inputLength = (*input.rows) * (*input.cols); 
  for (int i = 0; i < inputLength; i++){
    *(output -> data + i).r = *(input -> data + i) * pow(2, factor);
    *(output -> data + i).g = *(input -> data + i) * pow(2, factor);
    *(output -> data + i).b = *(input -> data + i) * pow(2, factor);

  }
}

//Performs blending of two image files by a certain factor              
void blend(Image *imput1, Image *input2, Image *output, double factor ){

  int outputLength = (*output.rows) * (*output.cols);

  int rowTracker = 1; //what row you are in 
  int colTracker = 1; //what col you are in 
  
  for (int i = 0; i < outputLength; i++){
    
    //case where input 2 has more cols than input 1
    if (colTracker > (input1 -> cols)){          
      ((output -> data + i) -> r) = ((input2 -> data + i) -> r);
      ((output -> data + i) -> g) = ((input2 -> data + i) -> g);
      ((output -> data + i) -> b) = ((input2 -> data + i) -> b);
    }
    
    //vice versa case
    else if (colTracker > (input2 -> cols)){      
      ((output -> data + i) -> r) = ((input1 -> data + i) -> r);
      ((output -> data + i) -> g) = ((input1 -> data + i) -> g);
      ((output -> data + i) -> b) = ((input1 -> data + i) -> b);
    }
    
    //case where input 2 has more rows than input 1
    else if (rowTracker > (input1 -> rows)){  	                       
      ((output -> data + i) -> r) = ((input2 -> data + i) -> r);
      ((output -> data + i) -> g) = ((input2 -> data + i) -> g);
      ((output -> data + i) -> b) = ((input2 -> data + i) -> b);
    }
    
    //vice versa case
    else if (rowTracker > (input2 -> rows)){                                                         
      ((output -> data + i) -> r) = ((input1 -> data + i) -> r);
      ((output -> data + i) -> g) = ((input1 -> data + i) -> g);
      ((output -> data + i) -> b) = ((input1 -> data + i) -> b);
    }
    
    //case when output index is within bounds of both inputs
    else{                                       
    ((output -> data + i) -> r) = (factor * ((input1 -> data + i) -> r)) + ((1 - factor) * ((input2 -> data + i) -> r));
    ((output -> data + i) -> g) = (factor * ((input1 -> data + i) -> g)) + ((1 - factor) * ((input2 -> data + i) -> g));
    ((output -> data + i) -> b) = (factor * ((input1 -> data + i) -> b)) + ((1 - factor) * ((input2 -> data + i) -> b));
    }
     
    //tracks the row
    colTracker++;
    if (colTracker == (*output.cols)){
      colTracker = 1;
      rowTracker++; 
    }
  }
  
}

//implementation of the zoomin function which zooms in on the input image by a factor of 2
//and produces an output image 4 times the area.
void zoomIN(Image *input, Image *output){

  int inputLength = (*input.rows) * (*input.cols);
  int outind = 0;
  int rowskip = 0;
  
  //Iterates through the output and input image.
  for (int i = 0; i < inputLength; i++){ 
    for (int j = 0; j < 4; j++){
      if (j > 1){
        *(output -> data + (rowskip * (*input.cols)) + (2 * i) + (*input.cols) + (j - 2)).r = *(input -> data + i).r;
        *(output -> data + (rowskip * (*input.cols)) + (2 * i) + (*input.cols) + (j - 2)).g = *(input -> data + i).g;
        *(output -> data + (rowskip * (*input.cols)) + (2 * i) + (*input.cols) + (j - 2)).b = *(input -> data + i).b;
      } else {
	    *(output -> data + (rowskip * (*input.cols)) + (2 * i) +j).r = *(input -> data + i).r;
        *(output -> data + (rowskip * (*input.cols)) + (2 * i) +j).g = *(input -> data + i).g;
        *(output -> data + (rowskip * (*input.cols)) + (2 * i) +j).b = *(input -> data + i).b;
      }
    }
    
    //allows for the second row to be skipped each time
    if ((i % (*input.cols)) == ((*input.cols) - 1)) {
      rowskip++;
    }
  }
}

//Performs zoomout function on the provided image                       
void zoomOUT(Image * input, Image *output){

  int rowskip = 0; 
  int outputLength = (*output.rows) * (*output.cols);
  
  //Loops through each pixel and condenses the average of 4 pixels into one pixel for color
  for (int i = 0 ; i < outputLength; i++) {
    
    *(output -> data + i).r = (*(input -> (data + (2 * i) + rowskip)).r + *(data + (2 * i) + 1 + rowskip).r + *(data + (2 *\
    i) + (*input.cols) + rowskip).r + *(data + (2 * i) + (*input.cols) + 1 + rowskip).r) / 4;

    *(output -> data + i).g = (*(input -> (data + (2 * i) + rowskip)).g + *(data + (2 * i) + 1 + rowskip).g + *(data + (2 *\
    i) + (*input.cols) + rowskip).g + *(data + (2 * i) + (*input.cols) + 1 + rowskip).g) / 4;

    *(output -> data + i).b = (*(input -> (data + (2 * i) + rowskip)).b + *(data + (2 * i) + 1 + rowskip).b + *(data + (2 *\
    i) + (*input.cols) + rowskip).b + *(data + (2 * i) + (*input.cols) + 1 + rowskip).b) / 4;
    
    //allows for the second row to be skipped each time
    if (i % (*output.cols) = (*output.cols) - 1){
      rowskip = rowskip + (*input.cols); 
    }
  }
}



