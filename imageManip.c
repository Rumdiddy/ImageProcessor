//Samuel Jin
//Ajay Ananthakrishnan
//sjin16
//aananth3

//imageManip.c
//Implementation of the operation functions in imageManip.h

#include "imageManip.h"
#include "ppm_io.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


//implementation of the exposure function which modifies the exposure of the input image 
//and writes the altered pixel values to the passed image.
void exposure(Image *input, double factor){

  int inputLength = ((*input).rows) * ((*input).cols);
  double value;
  for (int i = 0; i < inputLength; i++){
    value = input->data[i].r * pow(2, factor);
    input->data[i].r = overflowcheck(value);
    
    value = input->data[i].g * pow(2, factor);
    input->data[i].g = overflowcheck(value);

    value = input->data[i].b * pow(2, factor);
    input->data[i].b = overflowcheck(value);

  }
}

//Performs blending of two image files by a certain factor              
void blend(Image *input1, Image *input2, Image *output, double factor ){

  int outputLength = (output->rows) * (output->cols);

  int rowTracker = 0; //what row you are in 
  int colTracker = 0; //what col you are in 
  
  for (int i = 0; i < outputLength; i++){
    
    //case where input 2 has more cols than input 1
    if (colTracker > (input1 -> cols)){          
      output->data[i].r  = input2->data[i].r;
      output->data[i].g  = input2->data[i].g;
      output->data[i].b  = input2->data[i].b;
    }
    
    //vice versa case
    else if (colTracker > (input2 -> cols)){      
      output->data[i].r = input1->data[i].r;
      output->data[i].g = input1->data[i].g;
      output->data[i].b = input1->data[i].b;
    }
    
    //case where input 2 has more rows than input 1
    else if (rowTracker > (input1 -> rows)){  	                       
      output->data[i].r = input2->data[i].r;
      output->data[i].g = input2->data[i].g;
      output->data[i].b = input2->data[i].b;
    }
    
    //vice versa case
    else if (rowTracker > (input2 -> rows)){                                                
      output->data[i].r = input1->data[i].r;
      output->data[i].g = input1->data[i].g;
      output->data[i].b = input1->data[i].b;
    }
    
    //case when output index is within bounds of both inputs
    else{                                       
      output->data[i].r = (factor * input1->data[i].r) + ((1 - factor) * input2->data[i].r);
      output->data[i].g = (factor * input1->data[i].g) + ((1 - factor) * input2->data[i].g);
      output->data[i].b = (factor * input1->data[i].b) + ((1 - factor) * input2->data[i].b);
    }
     
    //tracks the row
    if (colTracker == ((output->cols) -1)){
      colTracker = 0;
      rowTracker++; 
    } else {
      colTracker++;
    }
  }
}

//implementation of the zoomin function which zooms in on the input image by a factor of 2
//and produces an output image 4 times the area.
void zoomIN(Image *input, Image *output){

  int inputLength = (input->rows) * (input->cols);
  int rowskip = 0;
  
  //Iterates through the output and input image.
  for (int i = 0; i < inputLength; i++){ 
    for (int j = 0; j < 4; j++){
      if (j > 1){
        output->data[(rowskip * (output->cols)) + (2 * i) + (output->cols) + (j - 2)].r = input->data[i].r;
	output->data[(rowskip * (output->cols)) + (2 * i) + (output->cols) + (j - 2)].g = input->data[i].g;
	output->data[(rowskip * (output->cols)) + (2 * i) + (output->cols) + (j - 2)].b = input->data[i].b;
      } else {
	output->data[(rowskip * (output->cols)) + (2 * i) + j].r = input->data[i].r;
	output->data[(rowskip * (output->cols)) + (2 * i) + j].g = input->data[i].g;
	output->data[(rowskip * (output->cols)) + (2 * i) + j].b = input->data[i].b;
      }
    }
    
    //allows for the second row to be skipped each time
    if ((i % (input->cols)) == ((input->cols) - 1)) {
      rowskip++;
    }
  }
}

//Performs zoomout function on the provided image                       
void zoomOUT(Image * input, Image *output){

  int rowskip = 0; 
  int outputLength = (output->rows) * (output->cols);
  
  //Loops through each pixel and condenses the average of 4 pixels into one pixel for color
  for (int i = 0 ; i < outputLength; i++) {
    
    (*(output -> data + i)).r = ((*((input->data) + (2 * i) + rowskip)).r + (*((input->data) + (2 * i) + 1 + rowskip)).r + (*((input->data) + (2 * i) + (input->cols) + rowskip)).r + (*((input->data) + (2 * i) + (input->cols) + 1 + rowskip)).r) / 4;

    (*(output -> data + i)).g = ((*((input->data) + (2 * i) + rowskip)).g + (*((input->data) + (2 * i) + 1 + rowskip)).g + (*((input->data) + (2 * i) + (input->cols) + rowskip)).g + (*((input->data) + (2 * i) + (input->cols) + 1 + rowskip)).g) / 4;

    (*(output -> data + i)).b = ((*((input->data) + (2 * i) + rowskip)).b + (*((input->data) + (2 * i) + 1 + rowskip)).b + (*((input->data) + (2 * i) + (input->cols) + rowskip)).b + (*((input->data) + (2 * i) + (input->cols) + 1 + rowskip)).b) / 4;
    
    //allows for the second row to be skipped each time
    if (i % (output->cols) == (output->cols) - 1){
      rowskip = rowskip + (input->cols); 
    }
  }
}


//performs in-place pointilism transformation
void pointilism(Image *input){
    
  //will this below line work?
  //determines 3% of pixels to be transformed
  int numPixelTransform = (input->rows) * (input->cols) * .03;

  int rand_x;
  int rand_y;
  int rand_rad;
  int numCols = (input -> cols);
  
  for (int i = 0; i <numPixelTransform; i = i + 1) {
    //selects rand x, y, and radius coordinates for circle
    rand_x = (rand() % (input->cols));
    rand_y = (rand() % (input->rows));
    rand_rad = (rand() % 5) + 1;

    //equation of filled circle:  (x - a)^2 + (y - b)^2 <= radius^2
    //iterates through all possible values of a (in this case j) and b (in this case k)
    for (int j = rand_x - rand_rad; j <= rand_x + rand_rad; j++) {
      for (int k = rand_y - rand_rad; k <= rand_y + rand_rad; k++) {
 
	//if (x - a)^2 + (y - b)^2 <= radius^2, then perform transformation
	if(k > 0 && j > 0 && k < (input->rows) && j < (input->cols)) {
	  if (pow((rand_x - j), 2) + pow((rand_y - k), 2) <= pow(rand_rad,2)) {
	    input->data[((numCols * k) + j)].r = input->data[((numCols * rand_y) + rand_x)].r;
	    input->data[((numCols * k) + j)].g = input->data[((numCols * rand_y) + rand_x)].g;
	    input->data[((numCols * k) + j)].b = input->data[((numCols * rand_y) + rand_x)].b;
	  }
	}
      }
    }
  }
}
