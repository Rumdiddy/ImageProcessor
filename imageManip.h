//Samuel Jin
//Ajay Ananthakrishnan
//sjin16
//aananth3

//imageManip.h
//Headerfile for all the operations functions

//performs exposure functin on input image
//returns output image pointer. 
Image * exposure(Image *input, Image *output, double factor);

//Performs zoomin function on the provided image
//writes output into empty output image.
Image * zoomIN(Image *input, Image *output);

//
Image *blend(Image *imput1, Image *input2, Image *output, double factor ); 
