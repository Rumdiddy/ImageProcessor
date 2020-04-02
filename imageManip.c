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
	if(k >= 0 && j >= 0 && k < (input->rows) && j < (input->cols)) {
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

//performs swirl function                                                      
void swirl(Image * input, Image *output, int cX, int cY, int distortScale){

  double alpha;

  //(xSwColNum, ySwRowNum) initially set to (1,1)
  int xSwColNum = 1;   //column in input image
  int ySwRowNum = 1;   //row in input image
  int xOrigColNum; 
  int yOrigRowNum;
  
  int numCols = (output -> cols);
  int numRows = (output -> rows);

  while (ySwRowNum <= numRows) {   //while you aren't at the end of the image

    alpha = (sqrt(pow(((xSwColNum - 1) - cX), 2) + pow(((ySwRowNum - 1) - cY), 2)) / distortScale);

    //gets corresponding coordinates from original input image: (xOrigColNum, yOrigRowNum)
    xOrigColNum = (((xSwColNum - 1) - cX) * cos(alpha)) - (((ySwRowNum - 1) - cY) * sin(alpha)) + cX;
    yOrigRowNum	= (((xSwColNum - 1) - cX) * sin(alpha)) + (((ySwRowNum - 1) - cY) * cos(alpha)) + cY;
    
    //if (xOrigColNum, yOrigRowNum) coordinates are out of bounds, make corresponding swirl pixel black
    if (xOrigColNum < 0 || xOrigColNum > (numCols - 1) || yOrigRowNum < 0 || yOrigRowNum > (numRows - 1)) {
      output->data[(ySwRowNum - 1) * numCols + (xSwColNum - 1)].r = 0;
      output->data[(ySwRowNum - 1) * numCols + (xSwColNum - 1)].g = 0;
      output->data[(ySwRowNum - 1) * numCols + (xSwColNum - 1)].b = 0;  
    }

    //copy over original pixel color values to corresponding swirl pixel 
    else {
      output->data[((ySwRowNum - 1) * numCols) + (xSwColNum - 1)].r = input->data[((yOrigRowNum) * numCols) + (xOrigColNum)].r;
      output->data[((ySwRowNum - 1) * numCols) + (xSwColNum - 1)].g = input->data[((yOrigRowNum) * numCols) + (xOrigColNum)].g;
      output->data[((ySwRowNum - 1) * numCols) + (xSwColNum - 1)].b = input->data[((yOrigRowNum) * numCols) + (xOrigColNum)].b;
    }

    //update (xSwColNum, ySwRowNum) coordinates of swirl image
    if (xSwColNum % numCols == 0) {
      ySwRowNum++;
      xSwColNum = 1; 
    } else {    
      xSwColNum++;
    }
  }
}

void blur(Image * input, Image *output, double sigma){

  //creates Gaussian matrix with sigma parameter
  int nDim = 0;
  int center = 0;
  int xCoor = 0;
  int yCoor = 0;  
  int dX = 0;
  int dY = 0;

  const double PI = 3.14159265358979323846;
  //sigma = sigma + (fmod(sigma, 0.1));  //rounds sigma down 
    
  //code to determine dimensions of G. matrix
  if (fmod((sigma * 10), 2.0) == 0) {
    nDim = (int)(sigma * 10.0) + 1;
  }
  else {
    nDim = (int)(sigma * 10.0);
  }

  //This print statment fixed everything. IDK why but keep this here.
  printf("This is our solution to the blur.");
  printf("\33[2K\r");
  
  double * matrix = malloc((nDim * nDim) * sizeof(double)); //initializes G. matrix
  
  center = (nDim / 2); //if you hae a 5 by 5 matrix, the center will be (2,2)
  
  while (yCoor < nDim) {
    dX = abs(xCoor - center); //difference from center
    dY = abs(yCoor - center);

    //Gaussian Formula
    matrix[(yCoor * nDim) + xCoor] = (double)(1.0 / (2.0 * PI * pow(sigma, 2))) * exp(-((pow(dX, 2) + pow(dY, 2)) / (2.0 * pow(sigma, 2))));
       
    //Moves onto the next row
    if (xCoor == (nDim - 1)) {
      xCoor = 0;
      yCoor++;
    } else {
      xCoor++; 
    }
  }
  
  int imXCoor = 0;
  int imYCoor = 0;
  
  int matXCoor = -(nDim/2);
  int matYCoor = -(nDim/2);

  int numCols = (input->cols);
  int numRows = (input->rows);
  
  double weighted_sumR = 0;       //weightedSum vars for 3 color channels.
  double weighted_sumG = 0;
  double weighted_sumB = 0;
  double mat_sum = 0;

  
  while (imYCoor < numRows) {  //for every pixel in image

    //for every index in the Gaussian matrix. Works b/c last index: (nDim/2, nDim/2), sums to nDim
    while ( matYCoor <= (nDim/2)) {

      //if matrix is in bounds with respect to image
      if(((imXCoor + matXCoor) >= 0) && ((imXCoor + matXCoor) < numCols)) {
	if (((imYCoor + matYCoor) >= 0) && ((imYCoor + matYCoor) < numRows)) { 
	   weighted_sumR += matrix[(matXCoor + (nDim/2)) + ((matYCoor + (nDim/2)) * nDim)] * input->data[imXCoor + matXCoor + ((imYCoor + matYCoor) * numCols)].r;
	   weighted_sumG += matrix[(matXCoor + (nDim/2)) + ((matYCoor + (nDim/2)) * nDim)] * input->data[imXCoor + matXCoor + ((imYCoor + matYCoor) * numCols)].g;
	   weighted_sumB += matrix[(matXCoor + (nDim/2)) + ((matYCoor + (nDim/2)) * nDim)] * input->data[imXCoor + matXCoor + ((imYCoor + matYCoor) * numCols)].b;
	   mat_sum += matrix[(matXCoor + (nDim/2)) + ((matYCoor + (nDim/2)) * nDim)];
	 }
      }

      //if you get to the end of a row in the matrix go to the start of the next row
      if (matXCoor == (nDim/2)) {
	matXCoor = -(nDim/2);
	matYCoor++; 
      }
      else {
	matXCoor++;
      }
    }

    output->data[imXCoor + ((imYCoor) * numCols)].r = (weighted_sumR / mat_sum);
    output->data[imXCoor + ((imYCoor) * numCols)].g = (weighted_sumG / mat_sum);
    output->data[imXCoor + ((imYCoor) * numCols)].b = (weighted_sumB / mat_sum);

    //reset weighted_sum for all 3 color values and mat_sum to 0 for next pixel.
    weighted_sumR = 0;
    weighted_sumG = 0;
    weighted_sumB = 0;
    mat_sum = 0;
    matYCoor = -nDim/2;
    matXCoor = -nDim/2;

    //if you get to end of a row in image array go to start of next row
    if (imXCoor == (numCols - 1)) {
      imXCoor = 0;
      imYCoor++; 
    }
    else{
      imXCoor++; 
    }
  }
  free(matrix);
}
