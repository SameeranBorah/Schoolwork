/*
 * test_client.c
 *
 *  Created on: Dec 5, 2014
 *      Author: Jesse Hamilton & John Lake
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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

struct connected_user{
	char username[NAME_SIZE];
	char groupname[NAME_SIZE];
	int socket;
};

int chat_connections[MAX_USERS];	// an array of socket descriptors
									// to send/forward messages to
int number_connects;				// Number of peers you're connected to
int server_socket;					// The socket file descriptor to the rendezvous server
char username[NAME_SIZE];
char groupname[NAME_SIZE];
char servername[NAME_SIZE];
struct connected_user **my_group;
int in_group;

pthread_t message_listener[MAX_USERS];
pthread_t thread_listen;
pthread_t thread_write;

struct chat_struct{
	int sockets[MAX_USERS];
	char groupName[NAME_SIZE];
	char userName[NAME_SIZE];
	int num_people_in_group;
	int num_connects;
};

struct forward_message_struct{
	int sockets[MAX_USERS];
	int socket_to_listen_to;
};

void receive_list(int socket){
	int total_groups;
	read_socket(socket,&total_groups,sizeof(int));
	total_groups = ntohl(total_groups);

	int i;
	for(i = 0; i < total_groups; i++){
		char gname[NAME_SIZE] = {'\0'};
		read_socket(socket,gname,NAME_SIZE);
		printf("%s\n",gname);
	}
}

void request_list(int socket){
	int send_bytes;
	char *message = "L";
	send_bytes = sizeof(message);
	int network_send_bytes = htonl(send_bytes);
	// Send size of message we're about to send
	write_socket(socket,&network_send_bytes,sizeof(int));

	// Send the actual message
	write_socket(socket,message,sizeof(message));
}

void message_sending_thread(void *socketfd){
	while(1){
		int socket = (int) socketfd;
		int prompt_size = 10;
		char *prompt = (char*) malloc(prompt_size*sizeof(char)+1);
		printf("%s >> ",groupname);
		getline(&prompt,&prompt_size,stdin);	// Get a prompt, i.e., leave, send, etc.

		int size = 1000;
		char message[1000] = {'\0'};

		if (strcmp(prompt,"send") == 0 || strcmp(prompt,"send\n") == 0) {	// User wants to send a message

			printf("Send >> ");
			char *sendString = (char*) malloc(size*sizeof(char)+1);
			getline(&sendString,&size,stdin);

			sendString[strlen(sendString) -1] = '\0';
			srand(time(NULL));
			int mesID = rand();
			int network_mes_ID = htonl(mesID);

			//message[strlen(message) - 2] = '\0';

			int mesLength = strlen(sendString);
			int network_mes_length = htonl(mesLength);


			//What you will send to all of the users on the chat group.
			//sprintf(message,"T%s:%s:%d:%d:%s:",groupName,userName,network_mes_ID,network_mes_length,sendString);
			sprintf(message,"T:%s:%s:%s:",groupname,username,sendString);

			//message[strlen(message)] = '\0';
			printf("Message you want to send: %s\n", message);

			int totalMessage = htonl(strlen(message));
			int i;
			for (i = 0; i < number_connects; ++i) {
				write_socket(my_group[i]->socket,&totalMessage,sizeof(int));
				write_socket(my_group[i]->socket,message,strlen(message));
			}
			free(sendString);
			//Send the message to all of the users you're connected to.  They will be responsible for forwarding.
			/*for(i=0;i<cstruct->num_connects;++i){
				write_socket(cstruct->sockets[i],&totalMessage,sizeof(int));
				write_socket(cstruct->sockets[i],message,strlen(message));
			}*/
		}

		else if(strcmp(prompt,"leave") == 0 || strcmp(prompt,"leave\n") == 0){	// User wants to leave the group
			sprintf(message,"L:%s:%s:",groupname,username);
			int totalMessage = htonl(strlen(message));
			int i;
			for (i = 0; i < number_connects; ++i){
				write_socket(my_group[i]->socket,&totalMessage,sizeof(int));
				write_socket(my_group[i]->socket,message,strlen(message));
				close(my_group[i]->socket);
				printf("Closed socket: %d\n",my_group[i]->socket);
				pthread_cancel(message_listener[i]);
			}

			pthread_cancel(thread_listen);

			// Tell the server that this user is leaving the group
			write_socket(server_socket,&totalMessage,sizeof(int));
			write_socket(server_socket,message,strlen(message));

			number_connects = 0;
			//main();
			in_group = 0;
			pthread_exit(NULL);
		}
	}
}

void forward_message(char *message, int size, int socket){
	write_socket(socket,&size,sizeof(int));
	write_socket(socket,message,size);
}

void wipe_user_data(struct connected_user* cu){
	memset(cu->groupname,'\0',NAME_SIZE);
	memset(cu->username ,'\0',NAME_SIZE);
	cu->socket = -1;
}

void remove_user_from_group(char *groupname, char *username){

	int i;
	for(i = 0; i < number_connects; ++i){
		printf("Comparing %s to %s && %s to %s\n",my_group[i]->groupname,groupname,my_group[i]->username,username);
		if(strcmp(my_group[i]->groupname,groupname) == 0 && strcmp(my_group[i]->username,username) == 0)
			break;	// This is the index to delete
	}
	if(i >= number_connects) return;	// You did not find this user in your group
	else {
		pthread_cancel(message_listener[i]);
		printf("Condemned user is at index %d\n",i);
		printf("Attempting to close socket: %d\n",my_group[i]->socket);
		close(my_group[i]->socket);
		printf("Closed socket: %d\n",my_group[i]->socket);
		int n;
		for(n = i; n < number_connects - 1; ++n){
			wipe_user_data(my_group[n]);
			strcpy(my_group[n]->groupname,my_group[n+1]->groupname);
			strcpy(my_group[n]->username,my_group[n+1]->username);
			my_group[n]->socket = my_group[n+1]->socket;
			// Must update pthreads too
			message_listener[n] = message_listener[n+1];
		}

		if(i == number_connects -1){
			wipe_user_data(my_group[i]);
		}else{
			wipe_user_data(my_group[n]);
		}



		number_connects--;	// Reduce your number of connections
		printf("Number of connections now %d\n",number_connects);

		if(number_connects == 0){
			
		}
	}

	//pthread_cancel(thread_listen);
}

void send_my_group_to_server(){

}

void handle_message(char *message){
	if(strlen(message) == 0) return;
	char m_copy[strlen(message)];
	strcpy(m_copy,message);
	char *first = strtok(m_copy,":");	// Grab the first letter to determine what to do with it
	char identifier = *first;
	switch(identifier){
	case 'T':
		printf("This is a normal message\n");
		char *gname = strtok(NULL,":");
		//printf("My groupname: %s\nIncoming groupname: %s\n",groupname,gname);
		char *uname = strtok(NULL,":");
		char *mbody = strtok(NULL,":");
		if(strcmp(gname,groupname) != 0) break;		// This is a message not intended for your group
		if(strcmp(uname,username)  == 0) break;		// You somehow received your own message
		printf("\n%s\n",mbody);
		break;
	case 'L':	// User wants to leave group and is sending message to neighbors
		gname = strtok(NULL,":");
		uname = strtok(NULL,":");
		printf("Attempting to remove %s from group %s\n",uname,gname);
		remove_user_from_group(gname,uname);
		break;
	default:
		break;
	}
}

void listen_for_messages(void *socketfd){

	int socket = (int) socketfd;

	while(1){
		char message[1000] = {'\0'};

		int message_size = 0;
		//printf("Waiting for a message on socket %d\n",socket);
		read_socket(socket,&message_size,sizeof(int));
		message_size = ntohl(message_size);
		if(message_size == 0) continue;
		read_socket(socket,message,message_size);
		printf("Received message: %s\n",message);
		handle_message(message);
		//printf("%s\n",message);
		int i;
		for(i = 0; i < number_connects; ++i){
			if(my_group[i]->socket == socket) continue;
			forward_message(message,message_size,my_group[i]->socket);
		}
	}

}

//Send the message "Q" to the server, to let it know that we are quitting. 
void end_session(int socket){
	int send_bytes;
	char *message = "Q";
	send_bytes = sizeof(message);
	int network_send_bytes = htonl(send_bytes);
	write_socket(socket, &network_send_bytes, sizeof(int));
	write_socket(socket,message,sizeof(message));
	exit(0);
}





//Listen for new connections.  If you get one, add it to the array of sockets to other users.
void listen_for_connections(void * cstruct){

	//listen on a port for other users coming in, and put those connections in an array.
	int backlog = 10;
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

	if ((aInfoStatus = getaddrinfo(NULL, CHATPORT, &hints, &res)) != 0) {
		printf("An error occurred in call to getaddrinfo()");
		return;
	}

	// Try different results in linked list to see what we can connect to
	for( ptr = res; ptr != NULL; ptr = ptr->ai_next) {

		if (( listenSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == -1) {
			//	printf("An error occurred in call to socket()\n");
			return;	// Go back to top of for-loop
		}

		if ( setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(uint32_t)) == -1) {
			//	printf("An error occurred in call to setsockopt()\n");
			return;
		}

		if ( bind( listenSocket, ptr->ai_addr, ptr->ai_addrlen) == -1) {
			close(listenSocket);
			//printf("An error occurred in call to bind()\n");
			return;
		}

		break;		// Exit for loop because socket() call was successful
	}

	if ( ptr == NULL) {
		// Never found a successful socket to connect to
		//printf("Error: No usable socket to connect to\n");
		return;
	}

	freeaddrinfo(res);

	if( listen (listenSocket, backlog) == -1){
		//	printf("An error occurred in call to listen()\n");
		return;
	}

	int done = 0;
	while(!done){
		sin_size = sizeof (theirAddress);
		printf("Waiting for new connection...\n");
		if((connectionSocket = accept(listenSocket,(struct sockaddr *)&theirAddress, &sin_size)) < 0){
			//printf("An error occurred in call to accept()\n");
			continue;
		}

		//inet_ntop(theirAddress.ss_family, get_in_addr((struct sockaddr *)&theirAddress),
		//		  ipstr, sizeof(ipstr));


		printf("NEW CONNECTION!\nNew socket is %d\n",connectionSocket);
		my_group[number_connects]->socket = connectionSocket;

		// Communicate with this new connection to get each other's info
		// Get this connection's info as well
		char theirInfo[2*NAME_SIZE] = {'\0'};
		int theirSize;
		read_socket(my_group[number_connects]->socket,&theirSize,sizeof(int));
		theirSize = ntohl(theirSize);
		read_socket(my_group[number_connects]->socket,theirInfo,theirSize);


		// Send my info to the new connection
		char myInfo[2*NAME_SIZE] = {'\0'};
		sprintf(myInfo,"%s:%s:",groupname,username);
		int myInfoSize = htonl(strlen(myInfo));
		write_socket(my_group[number_connects]->socket,&myInfoSize,sizeof(int));
		write_socket(my_group[number_connects]->socket,myInfo,strlen(myInfo));

		// Store the info they sent you
		char *theirGroup = strtok(theirInfo,":");
		char *theirUName = strtok(NULL,":");
		strcpy(my_group[number_connects]->groupname,theirGroup);
		strcpy(my_group[number_connects]->username,theirUName);
		printf("New connection is %s in group %s\n",theirUName, theirGroup);

		printf("Creating listening thread on socket %d\n",connectionSocket);
		pthread_create(&message_listener[number_connects], NULL, listen_for_messages, (void *) connectionSocket);
		number_connects++;
	}
 	pthread_exit(NULL);
}

void display_chat_thread(void *DCT_struct){
	int * socketfd = (int *) DCT_struct;

}



//Run a chat program with the others!
void run_chat(int sockets[MAX_USERS],char groupName[NAME_SIZE],char userName[NAME_SIZE],int num_people_in_group,int number_connects){

	printf("Making structure for threads!\n");
	struct chat_struct *cstruct = (struct chat_struct *) malloc(sizeof(struct chat_struct));
	int i;
	for(i=0;i<number_connects;++i){
		cstruct->sockets[i]=sockets[i];
		// For Jesse's listen for message
		int s = sockets[i];

		/*printf("Creating listening thread on socket %d\n",s);
		pthread_t message_listener;
		pthread_create(&message_listener, NULL, listen_for_messages, (void *) s);*/
	}
	printf("Done making sockets.\n");

	strcpy(cstruct->userName,userName);
	strcpy(cstruct->groupName,groupName);
	cstruct->num_people_in_group = num_people_in_group;
	cstruct->num_connects = number_connects;





	printf("Starting to chat\n");

	int done = 0;
	while(!done){
		struct chat_struct *chstr = (struct chat_struct*) cstruct;

		size_t size = 100;
		char *user_input = (char *) malloc (size*sizeof(char) + 1);

			//Prompt that tells us we're communicating with the server.
		printf("%s >> ",chstr->groupName);
		getline(&user_input,&size,stdin);
		char *first = strtok (user_input," ");

			//User wants to send a message:
		if(strcmp(first,"send\n")==0 || strcmp(first,"send")==0){
			printf("Send >");
			char *sendString = (char*) malloc(size*sizeof(char)+1);
			getline(&sendString,&size,stdin);

			char message[12+strlen(sendString)+strlen(userName)+strlen(groupName)];
			memset(message,'\0',sizeof(message));

			srand(time(NULL));
			int mesID = rand();
			int network_mes_ID = htonl(mesID);

			message[strlen(message) - 2] = '\0';

			int mesLength = strlen(sendString);
			int network_mes_length = htonl(mesLength);


			//What you will send to all of the users on the chat group.
			sprintf(message,"T%s:%s:%d:%d:%s:",groupName,userName,network_mes_ID,network_mes_length,sendString);

			message[strlen(message) - 2] = '\0';
			printf("Message you want to send: %s\n", message);

			int totalMessage = htonl(strlen(message));
			//Send the message to all of the users you're connected to.  They will be responsible for forwarding.
			for(i=0;i<cstruct->num_connects;++i){
				write_socket(cstruct->sockets[i],&totalMessage,sizeof(int));
				write_socket(cstruct->sockets[i],message,strlen(message));
			}




		}
		else if (strcmp(first,"leave\n")==0 || strcmp(first,"leave")==0){
			done = 1;
		}
		
		
	}

	free(cstruct);


}


//Sends the join message (For example: "Jgroupname:username:"
void request_join(int socket, char gname[NAME_SIZE], char uname[NAME_SIZE]){

	char message[4+strlen(gname)+strlen(uname)];
	memset(message,'\0',sizeof(message));

	//Put the message type, group name, and username in the message
	sprintf(message,"J%s:%s:",gname,uname);
	//strcat(message,gname); strcat(message,":"); strcat(message,uname); strcat(message,":");
	printf("%s\n",message);

	//Send the size of the message and the message itself
	int send_bytes = strlen(message);
	int network_send_bytes = htonl(send_bytes);
	write_socket(socket,&network_send_bytes,sizeof(int));
	write_socket(socket,message,strlen(message));
}




void talk_to_server() {

	//server_socket = client_TCP_connect(servername,PORT);
	int sockets_to_users[MAX_USERS];
	int number_of_connections =0;
	int needs_connection = 1;

	//Main loop for talking with the server:
	int done = 0;
	while(!done){

		if(needs_connection){
			printf("Attempting to connect to %s at %s\n",servername,PORT);
			server_socket = client_TCP_connect(servername,PORT);
			needs_connection = 0;
		}

		size_t size = 100;
		char *user_input = (char *) malloc (size*sizeof(char) + 1);

		//Prompt that tells us we're communicating with the server.
		printf("P2PChat >> ");
		getline(&user_input,&size,stdin);
		char *first = strtok (user_input," ");



		//Get the commands from the client, and send them to the server:
		//List command returns all of the groups:
		if(strcmp(first,"list\n") == 0 || strcmp(first,"list") == 0){
			request_list(server_socket);
			receive_list(server_socket);
		}
		//Join command adds you to a group:"
		else if(strcmp(first,"join") == 0){
			char *gn = strtok(NULL," ");
			char *un = strtok(NULL," ");
			un[strlen(un)-1] = '\0';
			strcpy(groupname,gn); strcpy(username,un);
			char gname[NAME_SIZE], uname[NAME_SIZE];
			strcpy(gname,gn); strcpy(uname,un);
			request_join(server_socket,gname, uname);


			/* Jesse's version
			 *
			 */
			//Get the number of users in a group:
			int num_users_in_group;
			read_socket(server_socket,&num_users_in_group,sizeof(int));
			num_users_in_group = ntohl(num_users_in_group);
			printf("There are %d users in this group!\n",num_users_in_group);


			int message_size;
			read_socket(server_socket,&message_size,sizeof(int));
			message_size = ntohl(message_size);
			char message[message_size];
			memset(message,'\0',message_size);
			read_socket(server_socket,message,sizeof(message));
			printf("Received group list: %s\n",message);

			char *bad = strtok(message,":");

			int tok_count;
			char group_ips[MAX_USERS][IP_SIZE];

			for(tok_count = 0; tok_count < num_users_in_group; ++tok_count){
				char *username = strtok(NULL,":");
				char *IP = strtok(NULL,":");
				strcpy(group_ips[tok_count],IP);
			}

			int user_count = 0;
			int chatSocket = -1;

			if (num_users_in_group > 1) {
				for(user_count = 0; user_count < num_users_in_group ; ++user_count){
					printf("Attempting to connect to %s\n",group_ips[user_count]);
					chatSocket = client_TCP_connect(group_ips[user_count],CHATPORT);
					if(chatSocket != -1) break;		// You have a valid socket, break
				}
			}

			printf("Connected to %s\nChatSocket = %d\n",group_ips[user_count],chatSocket);
			if(chatSocket == -1){	// No suitable connections -- you're first!
				char *port = CHATPORT;
				pthread_create(&thread_listen, NULL, listen_for_connections,(void *)port );
			}
			else {	// You have a valid socket descriptor
				my_group[number_connects]->socket = chatSocket;
				// Communicate with this new connection to get each other's info
				char myInfo[2*NAME_SIZE] = {'\0'};
				sprintf(myInfo,"%s:%s:",groupname,username);
				int myInfoSize = htonl(strlen(myInfo));
				printf("Writing info to connection: %d bytes: %s\n",ntohl(myInfoSize),myInfo);
				write_socket(my_group[number_connects]->socket,&myInfoSize,sizeof(int));
				write_socket(my_group[number_connects]->socket,myInfo,strlen(myInfo));

				// Get this connection's info as well
				char theirInfo[2*NAME_SIZE] = {'\0'};
				int theirSize;
				printf("Reading from connection\n");
				read_socket(my_group[number_connects]->socket,&theirSize,sizeof(int));
				theirSize = ntohl(theirSize);
				read_socket(my_group[number_connects]->socket,theirInfo,theirSize);

				printf("Successfully read from connection\n");
				// Store the info they sent you
				char *theirGroup = strtok(theirInfo,":");
				char *theirUName = strtok(NULL,":");
				strcpy(my_group[number_connects]->groupname,theirGroup);
				strcpy(my_group[number_connects]->username,theirUName);

				// Now create thread for displaying incoming messages
				printf("Creating listening thread on socket %d\n",chatSocket);
				pthread_create(&message_listener[number_connects], NULL, listen_for_messages, (void *) chatSocket);

				number_connects++;
				char *port = CHATPORT;
				pthread_create(&thread_listen, NULL, listen_for_connections,(void *)port );

			}
			in_group = 1;
			int dummy = 0;

			printf("Creating message_sending_thread\n");
			pthread_create(&thread_write,NULL,message_sending_thread,&dummy);

			while(in_group){

			}
			needs_connection = 1;


			//At this point, you're now chatting with the rendezvouz server again.  (You've left the group.)
			number_of_connections=0;




		}
		else if(strcmp(first,"quit") == 0 || strcmp(first,"quit\n")==0){
			free(user_input);
			end_session(socket);
		}
		free(user_input);
	}
}





int main(int args, char **argv) {
	in_group = 0;
	number_connects = 0;			// Number of peers you're connected to
	memset(username ,'\0',NAME_SIZE);
	memset(groupname,'\0',NAME_SIZE);
	memset(servername,'\0',NAME_SIZE);
	strcpy(servername,argv[1]);
	my_group = malloc (MAX_USERS * sizeof(struct connected_user*));
	int i;
	for(i = 0; i < MAX_USERS; ++i){
		my_group[i] = malloc (sizeof(struct connected_user));
	}

	//Make a TCP socket and connect to the rendezvouz server
	//server_socket = client_TCP_connect(argv[1],PORT);
	//printf("Connected to server with socket %d\n", server_socket);

	//Talk to the rendezvouz server, which will connect you to other clients as well.
	talk_to_server();

	while(1){

	}

	// Free the malloc()'d memory
	for(i = 0; i < MAX_USERS; ++i){
		free(my_group[i]);
	}
	free(my_group);
	return 0;
}
