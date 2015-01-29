/*
 * network_connections.h
 *
 * This is a simple header file to assist
 * in connecting via TCP
 *
 *  Created on: Oct 21, 2014
 *      Author: John & Jesse
 */

#ifndef NETWORK_CONNECTIONS_H_
#define NETWORK_CONNECTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <mhash.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <time.h>



void* get_in_addr(struct sockaddr* sa){
	if(sa->sa_family == AF_INET) { 		// It's an IPv4 address
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	else {
		return &(((struct sockaddr_in6*)sa)->sin6_addr);
	}
}


//Have a client make a connection via TCP to a server
int client_TCP_connect(char * serverName, char * portNumber){
	int socketfd, aInfoStatus;
	struct addrinfo hints, *res, *ptr;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if((aInfoStatus = getaddrinfo(serverName, portNumber, &hints, &res)) != 0){
		printf("An error occurred in call to getaddrinfo()\n");
		return -1;
	}

	for (ptr = res; ptr != NULL; ptr = ptr->ai_next) {
		if (( socketfd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == -1) {
			printf("An error occurred in call to socket()\n");
			continue;
		}

		if ( connect(socketfd, ptr->ai_addr, ptr->ai_addrlen) == -1) {
			close(socketfd);		// This is a bad socket
			printf("An error occurred in call to connect()\n");
			continue;
		}

		break;	// If it reaches here, we have successfully connected to a socket
	}

	if (ptr == NULL) { 		// Never found a suitable connection
		printf("No suitable connection\n");
		return -1;
	}

	freeaddrinfo(res);

	return socketfd;	// The socket file descriptor used for read/write
}

int server_TCP_connect(char *portNumber, int backlog){
	int listenSocket, connectionSocket; 	// The first is for listening, the second is for the connection
	struct addrinfo hints, *res, *ptr;
	struct sockaddr_storage theirAddress;	// Info on incoming connection
	socklen_t sin_size;
	struct sigaction sa;
	char ipstr[INET6_ADDRSTRLEN];
	int aInfoStatus, yes=1;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // Use my own IP address

	if ((aInfoStatus = getaddrinfo(NULL, portNumber, &hints, &res)) != 0) {
		printf("An error occurred in call to getaddrinfo()");
		return -1;
	}

	// Try different results in linked list to see what we can connect to
	for( ptr = res; ptr != NULL; ptr = ptr->ai_next) {

		if (( listenSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == -1) {
			printf("An error occurred in call to socket()\n");
			continue;		// Go back to top of for-loop
		}

		if ( setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(uint32_t)) == -1) {
			printf("An error occurred in call to setsockopt()\n");
			return -1;
		}

		if ( bind( listenSocket, ptr->ai_addr, ptr->ai_addrlen) == -1) {
			close(listenSocket);
			printf("An error occurred in call to bind()\n");
			continue;
		}

		break;		// Exit for loop because socket() call was successful
	}

	if ( ptr == NULL) {
		// Never found a successful socket to connect to
		printf("Error: No usable socket to connect to\n");
		return -1;
	}

	freeaddrinfo(res);

	if( listen (listenSocket, backlog) == -1){
		printf("An error occurred in call to listen()\n");
		return -1;
	}

	sin_size = sizeof (theirAddress);

	if((connectionSocket = accept(listenSocket,
	   (struct sockaddr *)&theirAddress, &sin_size)) < 0){
		printf("An error occurred in call to accept()\n");
		return -1;
	}

	inet_ntop(theirAddress.ss_family, get_in_addr((struct sockaddr *)&theirAddress),
				ipstr, sizeof(ipstr));

	printf("Received connection from %s\n",ipstr);
	return connectionSocket;
}

void get_timestamp(char *t_stamp){
	/*struct timeval tv;
	gettimeofday(&tv,NULL);
	int hour =  (int) (((tv.tv_sec) / (60 * 60)) % 24) - 4;
	if (hour < 0) hour += 24;
	int minute= (int) (((tv.tv_sec) / 60) % 60);
	int second= (int) ((tv.tv_sec) % 60);
	int millis= (int) (tv.tv_usec);
	sprintf(t_stamp,"Timestamp: %d:%d:%d.%d", hour, minute, second, millis);*/
	time_t rawtime;
	struct tm * timeinfo;

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (t_stamp,80,"%F %X",timeinfo);

}

void write_tcp(int fd, const void *buffer, size_t size){
	int obytes;
	if(( obytes = write(fd, buffer, size)) < 0) {
		fprintf(stderr,"An error occurred in write()\n");
		exit(1);
	}
}

void read_tcp(int fd, void *buffer, size_t size){
	int ibytes;
	if(( ibytes = read(fd, buffer, size)) < 0) {
		fprintf(stderr,"An error occurred in read()\n");
		exit(1);
	}
}
#endif /* NETWORK_CONNECTIONS_H_ */
