/*
 * John F. Lake, Jr. 
 * CSE 30341
 * Project 1: copyit program extra credit
 * This program copies files recursively from one directory to another.
 */



#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

//Number of bytes transferred per directory:
#define NOBYTES 256 
#define ARGER 1
#define REAER 2
#define WRIER 3
#define OTHER 4


//#define DEBUG 1 //Used for debugging (printing out file contents, among other things.)

/*
 * Error function; Uses strerror to give a more descriptive error, and the error codes 
 * can give the user extra information about where the error comes from.  
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
			printf("copyit: Error reading.\n");
			printf("copyit: %s\n",strerror(errno)); 
			exit(1); 
			break; 
		case WRIER:
			printf("copyit: Error writing.\n"); 
			printf("copyit: %s\n",strerror(errno)); 
			exit(1); 
			break; 
		case OTHER:
			printf("copyit: %s\n",strerror(errno)); 
			exit(1); 
			break; 	
	}
}


/*
 * Copy Status Update
 * @param s The alarm variable
 * @return void
 */
void copyStatus(int s){
	//Error Checking in place for return values:
	if(printf("copyit: Still copying...\n")<0) error(OTHER); 
	if(alarm(1)<0) error(OTHER); 
}
	

/*
 * Close the program.
 * @param b The number of bytes copied from the source file to the destination file.
 * @return void
 */
void closeProg(int b,char* src, char* dest){
	if(alarm(1)<0) error(OTHER); 
	if(printf("copyit: %d bytes were copied from %s to %s\n",b,src,dest)<0) error(OTHER);
}


/*
 * Function to copy individual files 
 * @param file1 The source File
 * @param file2 The target File
 */
int copyFile(char* file1, char* file2){
	int totalBytes=0; 
	int sp=0; //File descriptor for source program
	int tp=0; //File descriptor for target program
	int numBytes=0; //Number of bytes read or written
	char * buf=NULL; //Buffer that has NOBYTES (number of bytes); used to read and write 
	buf = malloc(sizeof(char)*NOBYTES); 


	

	//Open the source file
	if((sp = open(file1,O_RDONLY))==-1){
		//Error, value of -1 returned
		error(REAER); 
	}else{
		//Want to open the file we're going to write to: 
		if((tp=creat(file2,S_IRUSR|S_IWUSR))==-1){
			//Error creating file.
			error(WRIER); 
		}else{


			//Here, we have successfully opened both files.
			//Want to read from file: 
			do{
				memset(buf,0,sizeof(buf)); 
				if((numBytes = read(sp,buf,NOBYTES))==-1){
					//Error reading from file
					//Deal with error here.
					//Check to see if it was from the signalAction
					if(errno == EINTR){
						//Try to read again.
						continue; 
					}else{
						error(REAER); 
					}
				}else{

					//Increment the total number of bytes copied: 
					totalBytes+=numBytes;

					#ifdef DEBUG
						//Print out results: 
						if(printf("%s",buf)<0) error(OTHER); 
					#endif


					//Take the buffer and write to the other file
					if((write(tp,buf,strlen(buf)))==-1){
						//If it's an interrupt, try writing again, otherwise, exit.
						if(errno == EINTR){
							//Try to read again.
							continue; 
						}else{
							error(WRIER); 
						}
					}
					if(numBytes < NOBYTES) numBytes = 0; 
				}
			}while (numBytes>0);	
		}
		//Need to close the files:
		if(close(sp)<0) error(OTHER);
		if(close(tp)<0) error(OTHER);
	}

	//Deallocate memory and give a closing message to the user. 
	free(buf); 	
	return totalBytes;
}




/*
* Function to copy a directory recursively into another one. Carries out the bulk of this program. 
* @param dir1 The source directory
* @param dir2 The target directory
* @return void
*/ 
void copyDirectory(char* dir1, char* dir2,int *val){

	//check is used to tell what sort of file it is. 
	struct stat check;
	DIR* sd = NULL;

	//Ent is the directory entitiy used to see all of the files.
	struct dirent *ent=NULL;

	if((sd = opendir(dir1)) == NULL){
		error(REAER);
	}else{
		while((ent = readdir(sd))!=NULL){
			char* fullFilePath = malloc(100); 
			strcpy(fullFilePath,dir1);
			strcat(strcat(fullFilePath,"/"),ent->d_name);
			lstat(fullFilePath,&check);
			if(S_ISDIR(check.st_mode)){
				if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0){
					//Need to recurse and copy the directory here.
					char *copyDir1=malloc(100);
					char *copyDir2=malloc(100);
					strcpy(copyDir1,dir1);
					strcpy(copyDir2,dir2); 
					strcat(strcat(copyDir1,"/"),ent->d_name);
					strcat(strcat(copyDir2,"/"),ent->d_name);
					mkdir(copyDir2,0777);
					copyDirectory(copyDir1,copyDir2,val);		
					free(copyDir1);
					free(copyDir2);
				}
			}else{
				char *copyDir1=malloc(100);
				char *copyDir2=malloc(100);
				strcpy(copyDir1,dir1);
				strcpy(copyDir2,dir2);
				strcat(strcat(copyDir1,"/"),ent->d_name);
				strcat(strcat(copyDir2,"/"),ent->d_name);
				*val+=copyFile(copyDir1,copyDir2);
				free(copyDir1);
				free(copyDir2);
			}
			strcpy(ent->d_name,"\0");	
			free(fullFilePath);
		}
	}
	closedir(sd);
}


int main(int argc,char** argv){
	int totalBytes=0; //In this version, this will be the number of bytes transferred between directories.  

	//sigaction() is more portable than signal():
	struct sigaction sigAct;
	sigAct.sa_handler = copyStatus; 
	sigAct.sa_flags = SA_RESTART;

	//Use this to print if the file takes a long time to copy. 
	if(sigaction(SIGALRM,&sigAct,NULL)<0){
		error(OTHER);	
	}
	if(alarm(1)<0) error(OTHER); 
	mkdir(argv[2],0777);
	

	copyDirectory(argv[1],argv[2],&totalBytes);	

	//Deallocate memory and give a closing message to the user. 
	closeProg(totalBytes,argv[1],argv[2]);
	exit(0);
}

