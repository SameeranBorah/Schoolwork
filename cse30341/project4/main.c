/*
 * John F. Lake, Jr. 
 * CSE 30341
 * Project 4: Virtual Memory
 */

/*
Main program for the virtual memory project.
Make all of your modifications to this file.
You may add or rearrange any code or data as you need.
The header files page_table.h and disk.h explain
how to use the page table and disk interfaces.
*/

#define DEBUG 1

#include "page_table.h"
#include "disk.h"
#include "program.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>



//For the different page-replacement methods:
#define RAND 0
#define FIFO 1
#define CUST 2


//to tell if frames are empty or full: 
#define FREE 0
#define FULL 1



//Frame table to keep track of open frames.  
typedef struct ft{
	int numFrames;
	int method; 
	int * frames; 
	int full = 0;
} frame_table;

//Global because I can't edit the other file and need to pass this to the page_fault_handler function
frame_table f_table;




void page_fault_handler( struct page_table *pt, int page )
{
	printf("page fault on page #%d\n",page);

	//Function usage: 
	//page_table_set_entry(pagetable, pageNumber, frameNumber, write/read stuff):
	

	//Depending on the page replacement method, behave a certain way: 
	switch(f_table.method){
		case RAND:;
			long randomNumber = lrand48() % f_table.numFrames;
			#ifdef DEBUG
			printf("Using random method...\n");
			printf("Random number: %lu\n",randomNumber);
			
			#endif
			
			break;
		case FIFO: 
			#ifdef DEBUG
			printf("Using fifo method...\n");
			#endif
			break;
		case CUST:
			#ifdef DEBUG
			printf("Using custom method...\n");
			#endif
			break;
	}
	page_table_set_entry(pt,page,page,PROT_READ|PROT_WRITE);
	//exit(1);
}

int main( int argc, char *argv[] )
{
	
	//Seed the random number generator for lrand48():
	srand48((int) time(NULL));

	//If the number of arguments is incorrect:
	if(argc!=5) {
		printf("use: virtmem <npages> <nframes> <rand|fifo|custom> <sort|scan|focus>\n");
		return 1;
	}


	//Get the number of pages and frames from the command line arguments: 
	int npages = atoi(argv[1]);
	int nframes = atoi(argv[2]);
	f_table.numFrames = nframes;

	//Allocate the frame table:
	f_table.frames = malloc(sizeof(int)*f_table.numFrames);
	memset(f_table.frames,0,sizeof(f_table.frames));


	//Get the method for the page replacement, with a default of random. 
	const char *method = argv[3];
	if(!strcmp(method,"rand"))
		f_table.method = RAND;
	else if(!strcmp(method,"fifo"))
		f_table.method = FIFO;
	else if(!strcmp(method,"custom"))
		f_table.method = CUST;
	else {
		fprintf(stderr,"unknown method: %s\nDefaulting to random.\n",argv[3]);
		f_table.method = RAND;
	}

	#ifdef DEBUG
	printf("The number of frames to use is %d\n",f_table.numFrames);
	printf("The method to use is %d\n",f_table.method);
	int i;
	printf("Frame allocation:\n");
	for (i = 0;i<f_table.numFrames;i++)
		printf("Page %d: [%d]\n",i,f_table.frames[i]);
	#endif

	//Get the program to execute (sort, scan, or focus):
	const char *program = argv[4];

	//Create a new virtual disk, with an error message if there is a problem:
	struct disk *disk = disk_open("myvirtualdisk",npages);
	if(!disk) {
		fprintf(stderr,"couldn't create virtual disk: %s\n",strerror(errno));
		return 1;
	}


	//Create a new page table, with an error message if there is a problem:
	struct page_table *pt = page_table_create( npages, nframes, page_fault_handler );
	if(!pt) {
		fprintf(stderr,"couldn't create page table: %s\n",strerror(errno));
		return 1;
	}

	char *virtmem = page_table_get_virtmem(pt);
	char *physmem = page_table_get_physmem(pt);

	if(!strcmp(program,"sort")) {
		sort_program(virtmem,npages*PAGE_SIZE);

	} else if(!strcmp(program,"scan")) {
		scan_program(virtmem,npages*PAGE_SIZE);

	} else if(!strcmp(program,"focus")) {
		focus_program(virtmem,npages*PAGE_SIZE);

	} else {
		fprintf(stderr,"unknown program: %s\n",argv[4]);
	}

	page_table_delete(pt);
	disk_close(disk);

	return 0;
}
