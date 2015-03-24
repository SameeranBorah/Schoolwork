/*
 * John F. Lake, Jr. 
 * Multithreaded version of mandel.c
 * CSE 30341
 *
 */
#include "bitmap.h"
#include <pthread.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <string.h>

int iteration_to_color( int i, int max );
int iterations_at_point( double x, double y, int max );
void * compute(void * arg);
void compute_image( struct bitmap *bm, double xmin, double xmax, double ymin, double ymax, int max,int numThreads);

void show_help()
{
	printf("Use: mandel [options]\n");
	printf("Where options are:\n");
	printf("-m <max>    The maximum number of iterations per point. (default=1000)\n");
	printf("-x <coord>  X coordinate of image center point. (default=0)\n");
	printf("-y <coord>  Y coordinate of image center point. (default=0)\n");
	printf("-s <scale>  Scale of the image in Mandlebrot coordinates. (default=4)\n");
	printf("-W <pixels> Width of the image in pixels. (default=500)\n");
	printf("-H <pixels> Height of the image in pixels. (default=500)\n");
	printf("-o <file>   Set output file. (default=mandel.bmp)\n");
	printf("-h          Show this help text.\n");
	printf("\nSome examples are:\n");
	printf("mandel -x -0.5 -y -0.5 -s 0.2\n");
	printf("mandel -x -.38 -y -.665 -s .05 -m 100\n");
	printf("mandel -x 0.286932 -y 0.014287 -s .0005 -m 1000\n\n");
}

int main( int argc, char *argv[] )
{
	char c;

	// These are the default configuration values used
	// if no command line arguments are given.

	const char *outfile = "mandel.bmp";
	double xcenter = 0;
	double ycenter = 0;
	double scale = 4;
	int    numThreads = 1;
	int    image_width = 500;
	int    image_height = 500;
	int    max = 1000;

	// For each command line argument given,
	// override the appropriate configuration value.

	while((c = getopt(argc,argv,"x:y:n:s:W:H:m:o:h"))!=-1) {
		switch(c) {
			case 'n':
				numThreads = atoi(optarg);
				break;
			case 'x':
				xcenter = atof(optarg);
				break;
			case 'y':
				ycenter = atof(optarg);
				break;
			case 's':
				scale = atof(optarg);
				break;
			case 'W':
				image_width = atoi(optarg);
				break;
			case 'H':
				image_height = atoi(optarg);
				break;
			case 'm':
				max = atoi(optarg);
				break;
			case 'o':
				outfile = optarg;
				break;
			case 'h':
				show_help();
				exit(1);
				break;
		}
	}

	// Display the configuration of the image.
	printf("mandel: x=%lf y=%lf scale=%lf max=%d outfile=%s Threads=%d\n",xcenter,ycenter,scale,max,outfile,numThreads);

	// Create a bitmap of the appropriate size.
	struct bitmap *bm = bitmap_create(image_width,image_height);

	// Fill it with a dark blue, for debugging
	bitmap_reset(bm,MAKE_RGBA(0,0,255,0));

	// Compute the Mandelbrot image
	// Added in parameter for number of threads
	compute_image(bm,xcenter-scale,xcenter+scale,ycenter-scale,ycenter+scale,max,numThreads);

	// Save the image in the stated file.
	if(!bitmap_save(bm,outfile)) {
		fprintf(stderr,"mandel: couldn't write to %s: %s\n",outfile,strerror(errno));
		return 1;
	}

	return 0;
}



/*
Compute an entire Mandelbrot image, writing each point to the given bitmap.
Scale the image to the range (xmin-xmax,ymin-ymax), limiting iterations to "max"
*/

struct argStruct{
	int bw;
	int n;
	int width;
	int height;
	double xmin;
	double xmax;
	double ymin;
	double ymax;
	int max;
	struct bitmap *bm;
};


void*  compute(void * arg){
	
	struct argStruct *a = (struct argStruct *) arg;
	int i,j;
	for(j=a->bw*a->n;j<a->bw*(a->n+1);j++) {

		for(i=0;i<a->width;i++) {
			// Determine the point in x,y space for that pixel.
			double x = a->xmin + i*(a->xmax-a->xmin)/a->width;
			double y = a->ymin + j*(a->ymax-a->ymin)/a->height;
		

			// Compute the iterations at that point.
			int iters = iterations_at_point(x,y,a->max);

			// Set the pixel in the bitmap.
			bitmap_set(a->bm,i,j,iters);
		}
	}
	return NULL;
}

void compute_image( struct bitmap *bm, double xmin, double xmax, double ymin, double ymax, int max, int numThreads)
{

	//Make an array of the threads:
	pthread_t threads[numThreads];
	int n;
	int width = bitmap_width(bm);
	int height = bitmap_height(bm);

	// we will make a thread for different "bands" of the image. (horizontal stretches"
	int band_width = width/numThreads;

	for(n=0;n<numThreads;n++){
		struct argStruct * args = malloc(sizeof(struct argStruct));
		args->bw = band_width;
		args->n = n;
		args->width = width;
		args->height = height;
		args->xmin = xmin;
		args->xmax = xmax;
		args->ymin = ymin;
		args->ymax = ymax;
		args->max = max;
		args->bm = bm;
		
		pthread_create(&threads[n],NULL,compute,(void *) args);
	}

	for(n=0;n<numThreads;n++){
		pthread_join(threads[n],NULL);
	}


}





/*
Return the number of iterations at point x, y
in the Mandelbrot space, up to a maximum of max.
*/

int iterations_at_point( double x, double y, int max )
{
	double x0 = x;
	double y0 = y;

	int iter = 0;

	while( (x*x + y*y <= 4) && iter < max ) {

		double xt = x*x - y*y + x0;
		double yt = 2*x*y + y0;

		x = xt;
		y = yt;

		iter++;
	}

	return iteration_to_color(iter,max);
}

/*
Convert a iteration number to an RGBA color.
Here, we just scale to gray with a maximum of imax.
Modify this function to make more interesting colors.
*/

int iteration_to_color( int i, int max )
{
	int gray = 255*i/max;
	return MAKE_RGBA(gray,gray,gray,0);
}




