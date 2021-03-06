//Samuel Jin
//Ajay Ananthakrishnan
//sjin16
//aananth3

// ppm_io.h
// 601.220, Spring 2019

#ifndef PPM_IO_H
#define PPM_IO_H

#define _GNU_SOURCE
#include <stdio.h>

/* A struct to store a single RGB pixel, one byte per color channel.
 */
typedef struct _pixel {
  unsigned char r;  //red   channel value
  unsigned char g;  //green channel value
  unsigned char b;  //blue  channel value
} Pixel;


/* A struct to bundle together a pixel array with the other
 * image data we'll frequently want to pass around with it.
 * (This saves us from having to pass the same three 
 * variables to every function.) Note that no Pixels are
 * stored within this struct; the data field is a pointer.
 */
typedef struct _image {
  Pixel *data;  //pointer to array of Pixels
  int rows;     //number of rows of Pixels
  int cols;     //number of columns of Pixels
} Image;




/* Read a PPM-formatted image from a file (assumes fp != NULL).
 * Returns the address of the heap-allocated Image struct it
 * creates and populates with the Image data.
 */
Image * read_ppm(FILE *fp);


/* Write a PPM-formatted image to a file (assumes fp != NULL),
 * and return the number of pixels successfully written.
 */
int write_ppm(FILE *fp, const Image *im);

/* Checks the input command line arguments and ensures
 * that they are correct for the operation provided.
 * Returns the operation value 11-17.
 */
int arg_check(int argc, char *argv[]);

/* Generates output image to be filled. It determines
 * the output image size based on the operation specified.
 */
Image * gen_out(int oper, Image *input1, Image *input2);

//Checks value by value whether rgb values overflow 255
unsigned char overflowcheck(double rgb);

//Chooses which function to run.
void frun(int opval, Image * input1, Image * input2, Image * output, double factor);

#endif
