/*
 * constants.h
 *
 *  Created on: Dec 6, 2014
 *      Author: Jesse Hamilton & John Lake
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "network_connections.h"
#include "pthread.h"

#define MAX_USERS 100
#define PORT "9950"
#define CHATPORT "9421"
#define NAME_SIZE 64
#define IP_SIZE INET6_ADDRSTRLEN
#define TOTAL_GROUPS 50


struct user {
	char username[NAME_SIZE];
	char IP[IP_SIZE];
	pthread_t in_group_req_thread;
	int socket;
};

struct chat_group {
	char groupname[NAME_SIZE];
	struct user *users[MAX_USERS];
	int num_users;
};

void hton_user(struct user *u){

}

void ntoh_user(struct user *u){

}

void init_chat_group(struct chat_group *cg){
	memset(cg,0,sizeof(struct chat_group));
}

void init_user(struct user *u) {
	memset(u,0,sizeof(struct user));
}

void print_user(struct user *u){
	printf("Username: %s\nIP: %s\n",u->username, u->IP);
}


void write_user(int socket, struct user *u){
	hton_user(u);
	write_socket(socket,u->username,NAME_SIZE);
	write_socket(socket,u->IP, IP_SIZE);
	ntoh_user(u);
}

void receive_user(int socket, struct user *u){
	read_socket(socket,u->username,NAME_SIZE);
	read_socket(socket,u->IP,IP_SIZE);
	ntoh_user(u);
}

void slice_string(char *dest, char *src, int n){
	/*
	 * This function will copy char's n to the end of src
	 * into dest
	 */
	int i;
	for(i = n; i < strlen(src); ++i){
		dest[i-n] = src[i];
	}
	//dest[i] = '\0';
}
#endif /* CONSTANTS_H_ */
