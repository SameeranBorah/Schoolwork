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
#define MAX 50000

//Frame table to keep track of open frames.  
typedef struct ft{
	int numFrames;
	int numPages;
	int method; 

	//Each entry in this array is the page that maps to it
	int * framesToPages; 
	int * pagesToFrames;
	int * pagesWritten;

	int full;
	int frameOn;
} frame_table;



//Global because I can't edit the other file and need to pass this to the page_fault_handler function
frame_table f_table;
int diskReads = 0;
int diskWrites = 0;
int pageFaults = 0;
struct disk *disk = NULL; 
int * fifoQueue = NULL;
int customI =0;
int goDown = 0;


void page_fault_handler( struct page_table *pt, int page ){
	//increment the number of Page faults: 
	pageFaults++;
	char *physmem = page_table_get_physmem(pt);
	int *frame = malloc(sizeof(int));
	int *bits = malloc(sizeof(int));


	//Check if the page is already in the page table (need to update the bits)
	if(f_table.pagesWritten[page] >0){
		page_table_set_entry(pt,page,f_table.pagesToFrames[page],PROT_READ|PROT_WRITE);
	}

	//Otherwise, check if the table is full
	//If it's not full, every method fills it up the same way: 
	else if(!f_table.full){
		//Set the page table entry and read from the disk:
		page_table_set_entry(pt,page,f_table.frameOn,PROT_READ);
		disk_read(disk,page,&physmem[f_table.frameOn*PAGE_SIZE]);
		diskReads++;

		//Manage the frame table: 
		f_table.framesToPages[f_table.frameOn] = page;
		f_table.pagesWritten[page] = 1;
		f_table.pagesToFrames[page] = f_table.frameOn;
		fifoQueue[f_table.frameOn] = f_table.frameOn;

		//Find out if the table is full yet: 
		if(f_table.frameOn >= f_table.numFrames-1)
			f_table.full = 1;
		else
			f_table.frameOn++;

	//If it's full, decide how to replace the pages in each frame: 
	}else{
		int repFrame;
		int p,i;
		//Depending on the page replacement method, behave a certain way: 
		switch(f_table.method){

			//Random Method: 
			case RAND:;
				//Get the random number mod the number of frames
				repFrame = (int) lrand48() % f_table.numFrames;
				p = f_table.framesToPages[repFrame];
				page_table_get_entry(pt,p,frame,bits);

				//If it's dirty, wirte it to disk
				if(*bits == 3){ //3 meaning it has write privileges
					disk_write(disk,p,&physmem[(*frame)*PAGE_SIZE]);
					diskWrites++;
				}
				//Read the new page into the frame
				disk_read(disk,page,&physmem[(*frame)*PAGE_SIZE]);
				diskReads++;
				//Set the page table: 
				page_table_set_entry(pt,page,*frame,PROT_READ);
				page_table_set_entry(pt,p,*frame,0);
				//Set the frame table
				f_table.framesToPages[*frame] = page;
				f_table.pagesToFrames[page] = *frame;
				f_table.pagesToFrames[p] = -1;
				f_table.pagesWritten[page] = 1;
				f_table.pagesWritten[p] = 0;
				break;

			//First in, first out method: 
			case FIFO:; 
				//Get the number of the first frame in the stack
				repFrame = fifoQueue[0];

				//move all of the items on the stack
				for(i = 0;i<f_table.numFrames-1;i++){
					fifoQueue[i] = fifoQueue[i+1];
				} fifoQueue[f_table.numFrames-1] = repFrame;

				//If it's dirty, write to disk
				p = f_table.framesToPages[repFrame];
				page_table_get_entry(pt,p,frame,bits);
				if(*bits == 3){ //3 meaning it has write privileges
					disk_write(disk,p,&physmem[(*frame)*PAGE_SIZE]);
					diskWrites++;
				}
				
				//Read the new page into the frame
				disk_read(disk,page,&physmem[(*frame)*PAGE_SIZE]);
				diskReads++;
				//Set the page table: 
				page_table_set_entry(pt,page,*frame,PROT_READ);
				page_table_set_entry(pt,p,*frame,0);
				//Set the frame table
				f_table.framesToPages[*frame] = page;
				f_table.pagesToFrames[page] = *frame;
				f_table.pagesToFrames[p] = -1;
				f_table.pagesWritten[page] = 1;
				f_table.pagesWritten[p] = 0;
				break;
			//Custom is very simple; just go up and down 
			//(Increment until max, decrement until zero)
			case CUST:;
				repFrame = customI;
				if(goDown) 
					customI--;
				else
					customI++;
				if(customI == f_table.numFrames-1) 
					goDown = 1;
				else if (customI==0)
					goDown = 0;
		
				//If it's dirty, write to disk
				p = f_table.framesToPages[repFrame];
				page_table_get_entry(pt,p,frame,bits);

				if(*bits == 3){ //3 meaning it has write privileges
					disk_write(disk,p,&physmem[(*frame)*PAGE_SIZE]);
					diskWrites++;
				}
				//Read the new page into the frame
				disk_read(disk,page,&physmem[(*frame)*PAGE_SIZE]);
				diskReads++;
				//Set the page table: 
				page_table_set_entry(pt,page,*frame,PROT_READ);
				page_table_set_entry(pt,p,*frame,0);
				//Set the frame table
				f_table.framesToPages[*frame] = page;
				f_table.pagesToFrames[page] = *frame;
				f_table.pagesToFrames[p] = -1;
				f_table.pagesWritten[page] = 1;
				f_table.pagesWritten[p] = 0;
				break;
		}
	}
	//Free our variables
	free(frame);
	free(bits);
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

	if(npages<2 || nframes <2){
		printf("The number of frames or pages cannot be less than 2.\n");
		return 1;
	}
	f_table.numFrames = nframes;
	f_table.numPages = npages;
	f_table.full = 0;
	f_table.frameOn = 0;

	//Allocate the frame table, and the tables for the read/write bits:
	f_table.framesToPages = (int*) malloc(sizeof(int)*f_table.numPages);
	memset(f_table.framesToPages,0,sizeof(f_table.framesToPages));
	f_table.pagesWritten = (int*) malloc(sizeof(int)*f_table.numPages);
	memset(f_table.pagesWritten,0,sizeof(f_table.pagesWritten));
	f_table.pagesToFrames = (int*) malloc(sizeof(int)*f_table.numPages);
	memset(f_table.pagesToFrames,-1,sizeof(f_table.pagesToFrames));

	fifoQueue = malloc(sizeof(int)*f_table.numFrames);
	memset(fifoQueue,-1,sizeof(f_table.numFrames));

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


	//Get the program to execute (sort, scan, or focus):
	const char *program = argv[4];

	//Create a new virtual disk, with an error message if there is a problem:
	disk = disk_open("myvirtualdisk",npages);
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
	
	if(!strcmp(program,"sort")) {
		sort_program(virtmem,npages*PAGE_SIZE);
	} else if(!strcmp(program,"scan")) {
		scan_program(virtmem,npages*PAGE_SIZE);
	} else if(!strcmp(program,"focus")) {
		focus_program(virtmem,npages*PAGE_SIZE);
	} else {
		fprintf(stderr,"unknown program: %s\n",argv[4]);
	}
	printf("Page Faults: %d, Disk Reads: %d, Disk Writes: %d\n",pageFaults,diskReads,diskWrites);

	page_table_delete(pt);
	disk_close(disk);
	free(f_table.framesToPages);
	free(f_table.pagesWritten);
	free(f_table.pagesToFrames);

	return 0;
}
