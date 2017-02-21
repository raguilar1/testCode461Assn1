#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

#define QUEUE_LENGTH 10
#define RECV_BUFFER_SIZE 2048

/* TODO: server()
 * Open socket and wait for client to connect
 * Print received message to stdout
 * Return 0 on success, non-zero on failure
*/
int server(char *server_port) {
    int status;
	int s;
	int new_fd;
	char *buf;
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	int len, bytes_sent;
	struct addrinfo hints;
	struct addrinfo *servinfo;  // will point to the results
	int success;
	printf("1");
	memset(&hints, 0, sizeof hints); // make sure the struct is empty
	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;	// TCP stream sockets
	printf("2");
	// get ready to connect
	status = getaddrinfo(NULL, server_port, &hints, &servinfo);
	//Block 1
	//Block 2, get the socket, editted from 5.2
	printf("3");
	s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	printf("4");
	listen(s, QUEUE_LENGTH);
	printf("5");
	while(1){
		printf("Hi");
		addr_size = sizeof their_addr;
		new_fd = accept(s, (struct sockaddr *)&their_addr, &addr_size);
		success = 1;
		while(1){
			printf("Hi");
			success = recv(new_fd, &buf, RECV_BUFFER_SIZE, 0);
			if(success == -1 || success == 0){
				break;
			}
			printf(buf);
		}
	}
	
	
}

/*
 * main():
 * Parse command-line arguments and call server function
*/
int main(int argc, char **argv) {
  char *server_port;

  if (argc != 2) {
    fprintf(stderr, "Usage: ./server-c [server port]\n");
    exit(EXIT_FAILURE);
  }

  server_port = argv[1];
  return server(server_port);
}
