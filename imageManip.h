

//Samuel Jin
//Ajay Ananthakrishnan
//sjin16
//aananth3

//imageManip.h
//Headerfile for all the operations functions
#include "ppm_io.h"

//performs exposure functin on input image
//returns output image pointer. 
void exposure(Image *input, double factor);

//Performs zoomin function on the provided image
//writes output into empty output image.
void zoomIN(Image *input, Image *output);

//Performs zoomout function on the provided image
void zoomOUT(Image * input, Image *output);

//Performs blending of two image files by a certain factor
void blend(Image *imput1, Image *input2, Image *output, double factor ); 

//performs in-place pointilism transformation
void pointilism(Image *input);

//performs swirl function
void swirl(Image * input, Image *output, int cX, int cY, int distortScale);

//performs blur function
void blur(Image * input, Image *output, double sigma);
