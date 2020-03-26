#Samuel Jin
#Ajay Ananthakrishnan
#sjin16
#aananth3

CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g


project: project.o ppm_io.o imageManip.o
	$(CC) project.o imageManip.o ppm_io.o -lm -o project

project.o: project.c imageManip.h ppm_io.h
	$(CC) $(CFLAGS) -c project.c 

imageManip.o: imageManip.c imageManip.h
	$(CC) $(CFLAGS) -c imageManip.c -lm

ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c

clean:
	rm -f *.o project
