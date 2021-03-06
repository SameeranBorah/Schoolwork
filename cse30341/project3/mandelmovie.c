/*
 * John F. Lake, Jr. 
 * MandelMovie - Multiprocess generation of .bmp files
 * CSE 30341
 */



#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>




int main(int argc, char ** argv){

	int i; 
	int stat; 
	int numWanted = atoi(argv[1]);
	int numRunning =0;
	char * fileArg;
	char * sizeArg;
	char * xArg;
	char * yArg;
	char * mArg;

	if((fileArg = malloc(20))==NULL) printf("Error: %s\n",strerror(errno));
	if((sizeArg = malloc(20))==NULL) printf("Error: %s\n",strerror(errno));
	if((xArg = malloc(20))==NULL) printf("Error: %s\n",strerror(errno));
	if((yArg = malloc(20))==NULL) printf("Error: %s\n",strerror(errno));
	if((mArg = malloc(20))==NULL) printf("Error: %s\n",strerror(errno));
	pid_t pid;
	for(i = 1;i<51;i++){

		//Each time memset the arguments to mandel
		memset(fileArg,0,20);
		memset(sizeArg,0,20);
		memset(xArg,0,20);
		memset(yArg,0,20);
		memset(mArg,0,20);

		//Create a new process: 
		if((pid = fork())<0) printf("Error: %s\n",strerror(errno));

	
		//Child process: 
		if(pid == 0){
			//Execute mandel with the particular operations needed: 
			if(i<10){
				if((sprintf(fileArg,"-omandel0%d.bmp",i))<0) printf("Error: %s\n",strerror(errno));
			}else{
				if((sprintf(fileArg,"-omandel%d.bmp",i))<0)printf("Error: %s\n",strerror(errno));
			}
			float size = 1.0/i*2;
			if(size < 0.0001) size = 0.0001;
			if(sprintf(sizeArg,"-s %f",size)<0) printf("Error: %s\n",strerror(errno));
			if(sprintf(xArg,"-x .37")<0) printf("Error: %s\n",strerror(errno));
			if(sprintf(yArg,"-y .1")<0)printf("Error: %s\n",strerror(errno));;
			if(sprintf(mArg,"-m %d",100*i)<0)printf("Error: %s\n",strerror(errno));;
			char * fileArgs[7];

			fileArgs[0] = "./mandel";
			fileArgs[1] = fileArg;
			fileArgs[2] = sizeArg;
			fileArgs[3] = mArg;
			fileArgs[4] = xArg;
			fileArgs[5] = yArg;
			fileArgs[6] = NULL;
			if(execvp(fileArgs[0],fileArgs)<0) printf("Error: %s\n",strerror(errno));

		//Parent process
		}else{
			//You just forked, so increase the # of process running
			numRunning++;

			//If the number of processes running is more than the desired amount, wait for one to finish. 
			if(numRunning > numWanted){
				if(wait(&stat)<0) printf("Error: %s\n",strerror(errno));
			}
			continue;
		}
	}

	//Free all of the resources used: 
	free(fileArg);
	free(sizeArg);
	free(mArg);
	return 0;
}
