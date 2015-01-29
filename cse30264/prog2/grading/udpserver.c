/*
	John F. Lake, Jr. 
	CSE 30264
	Program 2 - simple UDP server; IP version agnostic
	
	This program accepts a UDP datagram message from a client, reverses it, and appends a microsecond accurate time stamp. 
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_LEN 5000




//Function to reverse a character array:
char* reverse(char * text){
	
	//Length of the string: 
	int len = strlen(text);
	
	
	//Make a temp char array with a large size
	char temp[BUFFER_LEN];  
	memset(&temp,0,sizeof(temp));  //make sure it's clear
	
	//Loop through the array and reverse it:
	int i;  
	for(i = 0; i<len; i++){
		temp[i] = text[len-1-i]; 
	}
	
	//Copy the temp char array to text and return it:
	strcpy(text,temp); 
	return text; 
}



//Main function: 
int main(int argc, char**argv){


//loop to receive multiple messages:
	while(1){
	
		//Necessary data elements
		int mysock; 
		int sr; 
		int numBytes; 
		struct addrinfo hints; 
		struct addrinfo *res; 
		socklen_t addr_len; 
		struct sockaddr_storage their_addr; 
		char buf[BUFFER_LEN]; 
		
	
		//Set the addrinfo as empty before starting
		memset(&hints,0,sizeof(hints)); 
	
		hints.ai_family = AF_INET; //IP Agnostic
		hints.ai_socktype = SOCK_DGRAM; //UDP
		hints.ai_flags = AI_PASSIVE; //Use my IP address

	
		
		memset(&buf[0], 0, sizeof(buf)); //set the buffer empty
		sr = getaddrinfo(NULL,argv[1],&hints,&res);  //Get address information, and set the port as the first argument
		if(sr != 0){
			printf("ERROR: COULD NOT GET ADDRESS INFORMATION!\n"); 
			exit(1); 
		}
	
	



		//make the socket
		mysock = socket(res->ai_family, res->ai_socktype,res->ai_protocol); 
		if(mysock==-1){
			printf("ERROR: SOCKET COULD NOT BE MADE.\n"); 
			exit(1); 
		}
		
		//bind
		bind(mysock, res->ai_addr, res->ai_addrlen); 


		//Receive a message from the client
		addr_len = sizeof their_addr;
		numBytes = recvfrom(mysock,buf,5000,0,(struct sockaddr *)&their_addr, &addr_len); 
		if(numBytes == -1){
			printf("ERROR: RECVFROM.\n"); 
			exit(1);
		}
		
		
		
	
		//Reverse the string
		reverse(buf);
		
		
		//Get and append a timestamp: 
		struct timeval t; 
		gettimeofday(&t,NULL); 
		t.tv_sec = (t.tv_sec % 86400)-(4*(3600)); 
		int hours = t.tv_sec/3600; 
		t.tv_sec = t.tv_sec - (hours*3600); 
		int minutes = t.tv_sec/60; 
		t.tv_sec = t.tv_sec - (minutes*60); 
		int secs = t.tv_sec; 
		int usecs = t.tv_usec; 
		char timestamp[100]; 
		sprintf(timestamp,"%d:%d:%d  %d\n",hours,minutes,secs,usecs);  
		strcat(buf,"  Timestamp:  ");
		strcat(buf,timestamp);  
		
		
	
	
		//Send back the message to the user: 
		numBytes = sendto(mysock,buf,strlen(buf),0,(struct sockaddr *)&their_addr, addr_len);
		if(numBytes == -1){
			printf("ERROR SENDING MESSAGE!\n"); 
			exit(1); 
		}
	
		//close the socket
		close(mysock); 
	}
}



