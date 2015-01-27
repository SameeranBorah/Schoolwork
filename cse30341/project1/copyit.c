/*
 *John F. Lake, Jr. 
 *CSE 30341
 *Project 1: copyit program
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#define NOBYTES 1024
#define ARGER 1
#define REAER 2
#define WRIER 3
//#define DEBUG 1 //Used for debugging (printing out file contents, among other things.)

/*
 * Error function
 * @param errorCode Signal corresponding to one of many error messages
 * @return void
 */
void error(int errorCode){
	switch(errorCode){
		case ARGER:
			printf("copyit: Wrong number of arguments!\n"); 
			printf("Usage: copyit <sourcefile> <targetfile>\n"); 
			exit(1); 
			break;
		case REAER:
			printf("copyit: %s\n",strerror(errno)); 
			exit(1); 
			break; 
		case WRIER:
			printf("copyit: Write error!\n"); 
			exit(1); 
			break; 
	}
}


/*
 * Copy Status Update
 * @param s The alarm variable
 */
void copyStatus(int s){
	printf("copyit: Still copying...\n"); 
	alarm(1); 
}

int main(int argc,char** argv){
	alarm(1);
	int sp; //File descriptor for source program
	int tp; //File descriptor for target program
	int numBytes; //Number of bytes read or written
	char * buf; //Buffer that has NOBYTES (number of bytes); used to read and write 
	buf = malloc(sizeof(char)*NOBYTES); 
	signal(SIGALRM,copyStatus);
	

	//If there are not exactly three arguments, send an error code to the user and exit. 
	if(argc!=3){
		error(ARGER); 
	}else{
		//Open the source file
		if((sp = open(argv[1],O_RDONLY))==-1){
 			//Error, value of -1 returned
 			error(REAER); 
 		}else{
			//Want to open the file we're going to write to: 
			if((tp=creat(argv[2],S_IRUSR|S_IWUSR))==-1){
				//Error creating file.
				error(WRIER); 
			}else{

				//Want to read from file: 
				do{
					memset(buf,0,sizeof(buf)); 
					if((numBytes = read(sp,buf,NOBYTES))==-1){
						//Error reading from file
						//Deal with error here.
							error(REAER); 
					}else{

						#ifdef DEBUG
							//Print out results: 
							printf("%s",buf); 
						#endif
						//Take the buffer and write to the other file
						if((write(tp,buf,strlen(buf)))==-1){
							error(WRIER); 
						}
						if(numBytes < NOBYTES) numBytes = 0; 
					}
				}while (numBytes>0);	
			}
		}
	}
	free(buf); 
}

