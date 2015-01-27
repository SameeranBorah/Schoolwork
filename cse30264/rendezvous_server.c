/*
 * rendezvous_server.c
 * This is the server that directs new users to chat groups.
 *
 *
 *  Created on: Dec 5, 2014
 *      Author: Jesse Hamilton & John Lake
 */


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
#include <sys/time.h>
#include <sys/stat.h>
#include <time.h>
#include <pthread.h>

#include "network_connections.h"
#include "constants.h"


// An array of all chat groups that are made by the users
struct chat_group *all_groups[TOTAL_GROUPS];

// Number of groups currently in existence; initially is zero.
int num_groups = 0;

//Struct used to hold the sockets and IP addresses of new users
struct handle_request_struct {
	int socketfd;
	char IP[IP_SIZE];
};

void *handle_request(void *hrs);


/*
	This function accepts a socket as a parameter and sends the list of current groups to that socket.
*/
void send_list(int socket) {

	// First, send an int of the total number of groups
	int network_num_groups = htonl(num_groups);
	write_socket(socket,&network_num_groups,sizeof(int));


	//Next, go through all of the groups and send them to the user.
	int i;
	for(i = 0; i < num_groups; i++){
		write_socket(socket,all_groups[i]->groupname, NAME_SIZE);
	}
}


/*
	This adds a group with group name "gname" to the list of groups
*/
void add_new_group(char gname[NAME_SIZE]){
	all_groups[num_groups] = (struct chat_group*) malloc (sizeof(struct chat_group));
	strcpy(all_groups[num_groups]->groupname,gname);
	num_groups++;
}


/*
  This returns the position in the list of the group with name "gname"
*/
int group_index(char *gname){
	int i;
	for(i = 0; i < num_groups; ++i){
		if(strcmp(all_groups[i]->groupname, gname) == 0)
			return i;
	}
	return -1;
}

/*
	Function to print all of the users for a particular group
*/
void print_group(int group_index){
	int i;
	for(i = 0; i < all_groups[group_index]->num_users; ++i){
		print_user(all_groups[group_index]->users[i]);
	}
}


/*
	This function removes a user from a particular group

*/
void remove_user_from_group_list(char *groupname, char *username){
	// TODO Receive the user to be deleted from the client and update the table. Should have a dedicated
	// thread running this function. Another thread should also be dedicated to sending down
	// new possible connections for when they run out
	char user_IP[IP_SIZE] = {'\0'};
	int user_socket;
	int gindex = group_index(groupname);
	print_group(gindex);
	pthread_t condemned_thread;

	//Iterate until you have the user you want at index i
	int i;
	for(i = 0; i < all_groups[gindex]->num_users; ++i){
		if(strcmp(all_groups[gindex]->users[i]->username,username) == 0)
			break;
	}


	if(i >= all_groups[gindex]->num_users) return; // User not in this group
	else {
		printf("Condemned user is at index %d\n",i);

		//u is the user we want to remove
		struct user *u = all_groups[gindex]->users[i];

		// These two values are for the call to handle_request
		strcpy(user_IP,u->IP);
		user_socket = u->socket;

		condemned_thread = u->in_group_req_thread;
		struct user *unext;

		int n;
		for(n = i; n < all_groups[gindex]->num_users - 1; n++){
			printf("Inside remove_user's for-loop()\n");
			u = all_groups[gindex]->users[n];
			unext = all_groups[gindex]->users[n+1];


			//Clear the user's information
			memset(u->username,'\0',NAME_SIZE);
			memset(u->IP,'\0',IP_SIZE);
			u->in_group_req_thread = 0;
			u->socket = -1;
			strcpy(u->username,unext->username);
			strcpy(u->IP,unext->IP);
			u->in_group_req_thread = unext->in_group_req_thread;
			u->socket = unext->socket;
		}
		if(all_groups[gindex]->num_users - 1 == i){		// If this condemned user is the last one in the group, only wipe it
			u = all_groups[gindex]->users[i];
			memset(u->username,'\0',NAME_SIZE);
			memset(u->IP,'\0',IP_SIZE);
			u->in_group_req_thread = 0;
			u->socket = -1;
		}
		else {	// Otherwise, wipe the next one too
			memset(unext->username,'\0',NAME_SIZE);
			memset(unext->IP,'\0',IP_SIZE);
			unext->in_group_req_thread = 0;
			unext->socket = -1;
		}
		all_groups[gindex]->num_users--;
		printf("Number of users in %s is now %d\n",groupname,all_groups[gindex]->num_users);
		print_group(gindex);
	}

	// Finish by creating a handle_request_struct and creating a pthread to it
	struct handle_request_struct *hrs = (struct handle_request_struct *) malloc (sizeof(struct handle_request_struct));
	hrs->socketfd = user_socket;
	strcpy(hrs->IP,user_IP);
	pthread_t handle_request_thread;
	printf("Calling handle_request thread");
	//pthread_create(&handle_request_thread, NULL, handle_request,(void *) hrs);
	pthread_cancel(condemned_thread);
	free(hrs);
}


/*
	This function handles messages that the user sends while in a particular chat group
*/
void handle_in_group_message(char *message){
	if(strlen(message)==0) return;	// Handle accidental empty messages

	//Get the message and put it in m_copy
	char m_copy[strlen(message)];
	strcpy(m_copy,message);

	// Grab the first letter to determine what to do with it
	char *first = strtok(m_copy,":");
	char identifier = *first;

	//Get the groupname, username, and the message that was sent.
	char *gname = strtok(NULL,":");
	char *uname = strtok(NULL,":");
	char *mbody = strtok(NULL,":");


	switch(identifier){
	case 'R':		// Request for users in specifed group for possible connections
		break;
	case 'L':	// User wants to leave group
		printf("Attempting to remove %s from group %s\n",uname,gname);
		remove_user_from_group_list(gname,uname);

		// Need to quit the handle_in_group_request thread
		break;
	default:
		break;
	}
}


/*
	Handles anything a user sends to this server while they are in a chat group
*/
void handle_in_group_requests(void *arg){

	//Socket of the particular user in question
	int socket = (int) arg;

	while(1){
		char message[1000] = {'\0'};
		int message_size = 0;
		//printf("Waiting for a message on socket %d\n",socket);

		//Get the size of the message from the user
		read_socket(socket,&message_size,sizeof(int));
		message_size = ntohl(message_size);
		printf("Received in handle_in_group_requests an int: %d\n",message_size);

		//Get the message from the user
		read_socket(socket,message,message_size);
		printf("Received message: %s\n",message);

		//Handle that message
		handle_in_group_message(message);
	}
}


/*
	Sends the group at group_index to the user on the socket provided
*/
void send_group(int group_index, int socket){
	char message[2048];
	memset(message,'\0',sizeof(message));
	strcat(message,"S");
	int i;
	struct chat_group *cg = all_groups[group_index];

	printf("Number of users in this group, server side: %d\n",cg->num_users); 


	//First, send the number of users that are in the group:
	int network_num_users = htonl(cg->num_users);
	write_socket(socket,&network_num_users,sizeof(int));


	//Next, send the message with the users:
	for(i = 0; i < cg->num_users; ++i){
		strcat(message,":");
		strcat(message,cg->users[i]->username);
		strcat(message,":");
		strcat(message,cg->users[i]->IP);
	}
	strcat(message,"::");
	//printf("Message to send: %s\n", message);

	//Send the size of the message
	int network_message_size = htonl(sizeof(message));
	write_socket(socket,&network_message_size,sizeof(int));

	//Send the message itself
	write_socket(socket,message,sizeof(message));
}


/*
	Currently not implemented
*/
void add_user_to_group(int gindex, int uindex, char uname[NAME_SIZE], char ip[IP_SIZE]){

}


/*
	This function handles all initial messages from the user to the rendezvous server.  
	It will: 
	-List the groups currently active
	-Allow the user to quit
	-Put a user in a particular group


*/
void *handle_request(void *hrs){
	struct handle_request_struct *args = (struct handle_request_struct *) hrs;
	printf("handle IP: %s\n",args->IP);
	int socket = args->socketfd;
	while(1){
		printf("In handle_request while(1)\n");

		//Get the size of the message from the user
		int recv_bytes;
		read_socket(socket,&recv_bytes,sizeof(int));
		recv_bytes = ntohl(recv_bytes);

		//If it's zero, it means there's no message
		if(recv_bytes == 0) continue;
		printf("recv_bytes = %d\n",recv_bytes);
		char request_message[recv_bytes];
		memset(request_message,0,recv_bytes);

		printf("Message before: %s\n",request_message);

		//Get the message from the user
		read_socket(socket,request_message,recv_bytes);

		printf("Message after: %s\n",request_message);


		//The client is requesting a list of the groups that exist
		if(strcmp(request_message,"L") == 0)
			send_list(socket);

		//The client is quitting the session and will disconnect.
		else if(strcmp(request_message,"Q") == 0){
			printf("Thread exiting...\n");
			pthread_exit(NULL);
		}
		// This is a join request
		else if(request_message[0] == 'J'){
			char info[recv_bytes];
			slice_string(info,request_message,1);
			printf("Sliced string: %s\n",info);
			char *gname = strtok(info,":");
			char *uname = strtok(NULL,":");

			/*struct user u;
			init_user(&u);
			strcpy(u.IP,args->IP);
			strcpy(u.username,uname);*/
			// Check if group exists
			int index = group_index(gname);
			int userIndex;
			if(index == -1){  // Group doesn't exist, so we need to create it:

				userIndex = 0;
				index = num_groups;
				printf("Creating group...\n");
				all_groups[index] = (struct chat_group*) malloc (sizeof(struct chat_group));
				strcpy(all_groups[index]->groupname,gname);
				all_groups[index]->users[0] = (struct user*) malloc (sizeof(struct user));

				strcpy(all_groups[index]->users[0]->IP, args->IP);
				printf("From handle_request: IP: %s\n",all_groups[num_groups]->users[0]->IP);
				strcpy(all_groups[index]->users[0]->username, uname);
				all_groups[index]->num_users = 1;
				num_groups ++;
				printf("Group created!\n");
			}
			// Group exists, so just add the user to the group
			else {
				userIndex = all_groups[index]->num_users;
				all_groups[index]->users[all_groups[index]->num_users] = (struct user*) malloc (sizeof(struct user));
				strcpy(all_groups[index]->users[all_groups[index]->num_users]->IP, args->IP);
				strcpy(all_groups[index]->users[all_groups[index]->num_users]->username, uname);
				all_groups[index]->num_users++;
			}

			all_groups[index]->users[userIndex]->socket = socket;
			send_group(index,args->socketfd);

			// Generate a thread that handles in-group requests, like leaving and member-update requests
			//pthread_t in_group_requests;
			pthread_create(&all_groups[index]->users[userIndex]->in_group_req_thread,NULL,handle_in_group_requests,(void *) args->socketfd);
			pthread_exit(NULL);
			return 0;	// In case thread exit didn't work
		}

		//pthread_exit(NULL);
	}
	pthread_exit(NULL);
}

int main() {
	int backlog = 10, done = 0;
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

	if ((aInfoStatus = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
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

	//If we cannot listen properly, exit the program.
	if( listen (listenSocket, backlog) == -1){
		printf("An error occurred in call to listen()\n");
		return -1;
	}
	printf("Server connected on socket %d\n", listenSocket);



	// Main accept loop -- will handle new connecting users
	while(!done){
		sin_size = sizeof (theirAddress);


		//Wait and accept new users connecting to the rendezvouz server
		printf("Waiting for new connection...\n");
		if((connectionSocket = accept(listenSocket,
		   (struct sockaddr *)&theirAddress, &sin_size)) < 0){
			printf("An error occurred in call to accept()\n");
			return -1;
		}

		//Get IP address information about the user that just connected
		inet_ntop(theirAddress.ss_family, get_in_addr((struct sockaddr *)&theirAddress),ipstr, sizeof(ipstr));

		//Structure used to pass the socket and IP address to the handle_request function:
		struct handle_request_struct *hrs = (struct handle_request_struct *) malloc (sizeof(struct handle_request_struct));

		//Assign the socket and IP address to the handle_request_struct "hrs"
		hrs->socketfd = connectionSocket;
		strcpy(hrs->IP,ipstr);
		printf("main: IP %s\n", hrs->IP);

		//Create a thread and handle the request from that particular user.
		pthread_t handle_request_thread;
		pthread_create(&handle_request_thread, NULL, handle_request,(void *) hrs);
	}

	/*char username[NAME_SIZE] = {'\0'};
	read_socket(socket,username,NAME_SIZE);
	printf("Username: %s\n",username);*/

	return 0;
}
