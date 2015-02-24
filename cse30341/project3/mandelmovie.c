#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(){

	int i; 
	pid_t pid;
	char * fileArg = malloc(20);
	char * sizeArg = malloc(20);
	char * mArg = malloc(20);
	for(i = 1;i<51;i++){
		memset(fileArg,0,20);
		memset(sizeArg,0,20);
		memset(mArg,0,20);
		pid = fork();
		if(pid == 0){
			//Execute mandel with the particular operations needed: 
			if(i<10){
				sprintf(fileArg,"-omandel0%d.bmp",i);
			}else{
				sprintf(fileArg,"-omandel%d.bmp",i);
			}
			float size = 1.0/i*2;
			if(size < 0.00001) size = 0.00001;
			sprintf(sizeArg,"-s %f",size);
			sprintf(mArg,"-m %d",100*i);
			char * fileArgs[4];
			fileArgs[0] = "./mandel";
			fileArgs[1] = fileArg;
			fileArgs[2] = sizeArg;
			fileArgs[3] = mArg;
			fileArgs[4] = NULL;
			execvp(fileArgs[0],fileArgs);
		}else{
			continue;
		}
	}
	free(fileArg);
	free(sizeArg);
	free(mArg);
	return 0;
}
