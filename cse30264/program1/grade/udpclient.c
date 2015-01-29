/*
	John F. Lake, Jr. 
	CSE 30264
	Program 1 - simple UDP client. 
This program accepts a text file or string as input, sends it to a server, and receives an inverted version with a time stamp back. 

*/



#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char**argv){


//structs for address info
struct addrinfo hints, *res, *p; 
int mySocket;  //int which will be a handle to the socket used
int status; 
int bytes; //Will record the number of bytes transmitted to and from the server
char buff[5000];  //Char array which will hold the sent and received messages. 




if(argc==4){	//If there are not 4 arguments (including the program name), print an error message. 
}
else{
	printf("Usage:  prog1 HOST PORT MESSAGE\n"); 
}


FILE *file;
if ((file = fopen(argv[3], "r")) == NULL)         //if the text argument isn't a file, copy it to the buffer
{
	strcpy(buff,argv[3]);
}
else{ //If it's a file, handle it. 
	
	//argv[3] is a file name:
	while(fgets(buff, 5000, file) != NULL){}
}

 
memset(&hints,0,sizeof(hints)); 
hints.ai_family = AF_INET; 
hints.ai_socktype = SOCK_DGRAM; //specify this for UDP data transfer 


status = getaddrinfo(argv[1],argv[2], &hints, &res); //get the address info for our structs
if(status!=0){
	printf("Error getting address info.\n"); 
}


//make a socket
mySocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

if(mySocket==-1){
	printf("ERROR: SOCKET COULD NOT BE MADE.\n"); 

}

//send the data
bytes = sendto(mySocket,buff,strlen(buff),0,res->ai_addr, res->ai_addrlen);

if(bytes ==-1)
	printf("ERROR WRITING TO SERVER\n"); 


//make new structs to receive data	
struct sockaddr_storage their_addr;
socklen_t addr_len; 
addr_len = sizeof their_addr; 
//receive the message from the server
bytes = recvfrom(mySocket, buff,5000, 0,(struct sockaddr *)&their_addr, &addr_len);  

if(bytes==-1)
	printf("ERROR READING FROM SERVER\n"); 
	
buff[bytes] = '\0';
//print out the message sent back
printf("%s \n",buff); 

//close the socket. 
close(mySocket); 

}
