/*
	John F. Lake, Jr.
	CSE 30264
	Project 1: Client for FTP Program
*/

//Necessary header files
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include "mhash.h"
#include <stdlib.h>


int main(int argc, char**argv){


	//structs for address info
	struct addrinfo hints, *res, *p; 
	int mySocket;  //int which will be a handle to the socket used
	int status; 
	int bytes; //Will record the number of bytes transmitted to and from the server
	char buff[5000];  //Char array which will hold the sent and received messages. 
	char * port;  
	char * response = malloc(sizeof(char)*500); 
	char * fileName = malloc(sizeof(char)*100);  
	int loop = 1; 
	
	
	//Get correct port.  Default is 9499
	if(argc == 3){
		port = argv[2]; 
	}else{
		port = "9499"; 
	}
	
	//printf("%s",port); 
	
	

	 
	//Set some variables in the structure relating to IP type and data transfer protocol
	memset(&hints,0,sizeof(hints)); 
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM; //specify this for TCP data transfer 


	//Get address information... argv[1] is the hostname
	status = getaddrinfo(argv[1],port, &hints, &res);
	if(status!=0){
		printf("Error getting address info.\n"); 
		exit(1); 
	}


	//make a socket
	if((mySocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol))==-1){
		printf("ERROR: SOCKET COULD NOT BE MADE.\n"); 
		exit(1); 
	}
	
	//connect to the server
	if(connect(mySocket,res->ai_addr,res->ai_addrlen)==-1){
		printf("ERROR: CONNECTION COULD NOT BE MADE.\n"); 
		exit(1); 
	}
	
	//Loop used to perform multiple FTP operations: 
	while(loop){
	
		//Prompt user and get response: 
		printf("What operation do you want to perform?  (get, put, dir, xit)\n"); 
		scanf("%s",response); 
		
	
		if(!strcmp(response,"get")){ 				//GET COMMAND 
			int size=0;     				//Size of the file
			int timeElapsed; 				//Used to calculate throughput
			
			//MD5 Hashing Values: 
			char hashValue[16]; 				
			char otherHashValue[16]; 
			
			
			FILE *saveFile;
			write(mySocket,response,sizeof(response));	//Tell server to get ready to retrieve the file. 
			
			//Get the name of the file
			printf("Enter the name of the file. Ex: 'file.c'\n");  
			scanf("%s",fileName); 
			
			
			//Client sends the length of the filename and the filename.
			short fileNameLength = strlen(fileName);  
			fileNameLength = htons(fileNameLength); 
			write(mySocket,&fileNameLength, sizeof(fileNameLength)); 
			fileNameLength = ntohs(fileNameLength); 
			write(mySocket,fileName,100); 
			
			
			//Client gets the size of the file
			read(mySocket,&size,sizeof(size));
			size = ntohl(size); 
			
			//If size==-1, the file doesn't exist on the server
			if(size == -1){ 
				printf("File does not exist.\n"); 
				
			//Otherwise, get the file.  
			}else{
				
				//Get the MD5 Hash value of the file on the server as a 16 Byte string
				read(mySocket,otherHashValue,16); 
				
				char fileBuffer[100];  	//C String to read each packet
				int received = 0; 	//Number of bytes received so far
				struct timeval t1;  	//Calculate time BEFORE the download finishes
				gettimeofday(&t1,NULL); 
				saveFile = fopen(fileName,"w");  //Open file for writing.
				
				//While we have not received all of the bytes, continue getting data. 
				while(received < size){
					int nread; //Number of bytes read
					read(mySocket,&nread,sizeof(nread)); 
					received = nread; 
					read(mySocket,fileBuffer,100);  
					fputs(fileBuffer,saveFile);  //Save each buffer to the file.  
				}
				fclose(saveFile); 
				struct timeval t2; 			//Calculate time AFTER download
				gettimeofday(&t2,NULL); 
				timeElapsed = t2.tv_usec -t1.tv_usec; 	//Calculate elapsed time (in microseconds). 
				
				//compute MD5 hash of the file retrieved.  
				MHASH hash; 
				hash = mhash_init(MHASH_MD5); 
				char buffer; 	
				saveFile = fopen(fileName,"r"); 
				while(fread(&buffer,1,1,saveFile)){
					mhash(hash,&buffer,1); 
				}
				mhash_deinit(hash,hashValue);
				fclose(saveFile); 
				
				
				//Test to see if the hashes are equivalent.  
				int i; int success=1; 
				for (i = 0; i < mhash_get_block_size(MHASH_MD5); i++) {
					if(hashValue[i] != otherHashValue[i]) success = 0; 
				}
		
				//If the MD5 hashes match, the transfer was sucessful.  Show the throughput    
				if(success){
					printf("Transfer succeeded.\n"); 
					printf("You transfered %d bytes in %d microseconds.\n",size,timeElapsed); 
					double bandwidth = ((size/1000000.0)/(timeElapsed/1000000.0)); 
					printf("Your bandwidth was %.2f MB/s.\n",bandwidth); 
					printf("File MD5 Hash:"); 
					for (i = 0; i < mhash_get_block_size(MHASH_MD5); i++) {
						printf("%x",hashValue[i]); 	
					}
					printf("\n"); 
				//Othewise, there was an error.  Return to the loop to prompt user
				}else{
					printf("Error transferring data.\n"); 
				}
				
			}
		} else if(!strcmp(response,"put")){ 				//PUT COMMAND
		
			write(mySocket,response,sizeof(response)); 		//Send command to server
			int size; int timeElapsed;
			FILE *loadFile;
			
			//Get file to send to the server
			memset(fileName,0,sizeof(fileName)); 
			printf("Enter the name of the file. Ex: 'file.c'\n"); 
			scanf("%s",fileName); 
			
			
			//Send the length of the filename as a 16 big int, and the fileName as a char array. 
			short fileNameLength = strlen(fileName);
			fileNameLength = htons(fileNameLength); 
			write(mySocket,&fileNameLength,sizeof(fileNameLength));
			fileNameLength = ntohs(fileNameLength); 
			write(mySocket,fileName,100); 
			
			//calculate the size of the file: 
			if(loadFile = fopen(fileName,"r")){
				struct stat st; 
				stat(fileName, &st); 
				size = st.st_size;  
				fclose(loadFile); 
			}else{
				size = -1; 
			}
			//Send the size as a 32 bit int to the server
			size = htonl(size); 
			write(mySocket,&size,sizeof(size)); 
			size = ntohl(size); 
			
			
			if(size == -1){
				printf("Error, file doesn't exist.\n"); 
			} else {
			
			
				
				char fileBuffer[101]; //Buffer to write to the server
				int sent = 0; 		//Used to calculate when to stop sending packets
				loadFile = fopen(fileName,"r"); //Load the file to read chunks from it. 
					
				struct timeval t1;  	//Calculate time BEFORE the download finishes
				gettimeofday(&t1,NULL); 
		
		
				//Send data to the server
				while(sent < size){
					size_t bytes_read; 
					memset(fileBuffer,0,sizeof(fileBuffer)); 
					bytes_read = fread(fileBuffer,1,sizeof(char)*100,loadFile); 
					sent+= (int) bytes_read;
					write(mySocket,&sent,sizeof(sent)); 
					write(mySocket,fileBuffer,100); 
				}
				//Close th file
				fclose(loadFile);
				struct timeval t2; 			//Calculate time AFTER download
				gettimeofday(&t2,NULL); 
				timeElapsed = t2.tv_usec -t1.tv_usec; 	//Calculate elapsed time (in microseconds). 
				
				
				//Compute the MD5 hash of the file:
				MHASH hash; 
				hash = mhash_init(MHASH_MD5); 
				char hashValue[16]; 
				char otherHashValue[16]; 
				char buffer; 	
				loadFile = fopen(fileName,"r"); 
				while(fread(&buffer,1,1,loadFile)){
					mhash(hash,&buffer,1); 
				}
				fclose(loadFile); 
				mhash_deinit(hash,hashValue);
				
				
				//Get the MD5 hash from the server
				read(mySocket,otherHashValue,16); 
				
				
				//Test to see if the hashes are equivalent.  
				int i; int success=1; 
				for (i = 0; i < mhash_get_block_size(MHASH_MD5); i++) {
					if(hashValue[i] != otherHashValue[i]) success = 0; 
				}
			
		
				//If the MD5 hashes match, the transfer was sucessful.  Show the throughput    
				if(success){
					printf("Transfer succeeded.\n"); 
					printf("You transfered %d bytes in %d microseconds.\n",size,timeElapsed); 
					double bandwidth = ((size/1000000.0)/(timeElapsed/1000000.0)); 
					printf("Your bandwidth was %.2f MB/s.\n",bandwidth); 
					printf("File MD5 Hash:"); 
					for (i = 0; i < mhash_get_block_size(MHASH_MD5); i++) {
						printf("%x",hashValue[i]); 	
					}
					printf("\n"); 
				
				//Othewise, there was an error.  Return to the loop to prompt user
				}else{
					printf("Error transferring data.\n"); 
				}
				
			}	

		} else if(!strcmp(response,"dir")){			//COMMAND TO GET DIRECTORY AT SERVER
			char file[100]; 				//C string used for the file names		
			int numOfFiles = 0; 				//Number of files in directory
			write(mySocket,response,sizeof(response));	//Tell the server to fetch directory information
			read(mySocket,&numOfFiles,sizeof(numOfFiles)); 	//Read the number of files in the directory
			numOfFiles = ntohl(numOfFiles); 
			printf("Files in the server directory: (%d total)\n",numOfFiles); //Give the number of files. 
			int i; 
			
			//Loop through and show the user each file in the directory. 
			for(i = 0; i<numOfFiles;i++){ 
				read(mySocket,file, sizeof(file));
				printf("%s",file); 
			}
			
			
		} else if(!strcmp(response,"xit")){ 			//EXIT COMMAND
			write(mySocket,response,sizeof(response)); 	//Let the server know to exit. 
			loop = 0; 					//Let the client know to stop looping. 
			printf("The session has ended.\n"); 		//Print message to user. 
			
			
		} else {						//ERROR MESSAGE & CONTINUE LOOP
			//If user doesn't enter any of the commands, output an error message and continue the loop.
			printf("Incorrect usage.  Enter 'get', 'put', 'dir', or 'xit'\n"); 
		}
	}
	close(mySocket);  //close the socket
}
