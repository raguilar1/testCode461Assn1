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
	//code bellow edited from http://beej.us/guide/bgnet/output/html/singlepage/bgnet.htm ch 5 and 6
    int status;
	int s;
	int new_fd;
	int bin;
	int listn;
	char buf[RECV_BUFFER_SIZE];
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	int len, bytes_sent;
	struct addrinfo hints;
	struct addrinfo *servinfo;  // will point to the results
	int bytes;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; 
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	// get ready to connect
	status = getaddrinfo(NULL, server_port, &hints, &servinfo);
	if(status != 0){
		fprintf(stderr, "getaddrinfo failed");
		return 1;
	}	
	//connect to socket
	s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if(s == -1){
		fprintf(stderr, "socket failed");
		return 2;
	}
	//bind 
	bin = bind(s, servinfo->ai_addr, servinfo->ai_addrlen);
	if(bin == -1){
		fprintf(stderr, "bind failed");
		return 3;
	}
	//listen
	listn = listen(s, QUEUE_LENGTH);
	if(listn == -1){
		fprintf(stderr, "listen failed");
		return 4;
	}	
	while(1){
		addr_size = sizeof their_addr;
		new_fd = accept(s, (struct sockaddr *)&their_addr, &addr_size);
		while(1){
			bytes = recv(new_fd, buf, RECV_BUFFER_SIZE, 0);
			if(bytes >= 0){
				buf[bytes] = '\0';
				printf(buf);
			}
			else{
				break;
				}
			
		}
		close(new_fd);
	}
	close(s);
	
	
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
