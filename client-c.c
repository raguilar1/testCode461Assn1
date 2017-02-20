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

#define SEND_BUFFER_SIZE 2048


/* TODO: client()
 * Open socket and send message from stdin.
 * Return 0 on success, non-zero on failure
*/
int client(char *server_ip, char *server_port) {
	//Block 1 : edited from 5.1
	int status;
	int s;
	int c;
	int len, bytes_sent;
	struct addrinfo hints;
	struct addrinfo *servinfo;  // will point to the results

	memset(&hints, 0, sizeof hints); // make sure the struct is empty
	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

	// get ready to connect
	status = getaddrinfo(server_ip, server_port, &hints, &servinfo);
	//Block 1
	//Block 2, get the socket, editted from 5.2
	s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	//Block 2
	//Block 3, edited frmo 5.4
	connect(s, servinfo->ai_addr, servinfo->ai_addrlen);
	//Block 3
	while(1){
		c = getchar( );
		if(c == -1) break;
		send(s, &c, 1, 0);
	}
	  
}

/*
 * main()
 * Parse command-line arguments and call client function
*/
int main(int argc, char **argv) {
  char *server_ip;
  char *server_port;

  if (argc != 3) {
    fprintf(stderr, "Usage: ./client-c [server IP] [server port] < [message]\n");
    exit(EXIT_FAILURE);
  }

  server_ip = argv[1];
  server_port = argv[2];
  return client(server_ip, server_port);
}
