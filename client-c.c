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
	//code bellow edited from http://beej.us/guide/bgnet/output/html/singlepage/bgnet.htm ch 5 and 6
	int status;
	int s;
	int c;
	int len, bytes_sent;
	int con;
	struct addrinfo hints;
	struct addrinfo *servinfo;  

	memset(&hints, 0, sizeof hints); 
	hints.ai_family = AF_UNSPEC;     
	hints.ai_socktype = SOCK_STREAM; 

	// get ready to connect
	status = getaddrinfo(server_ip, server_port, &hints, &servinfo);
	if(status != 0){
		fprintf(stderr, "getaddrinfo failed");
		return 1;
	}
	//open socket
	s = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if(s == -1){
		fprintf(stderr, "socket failed");
		return 2;
	}
	
	//connect
	con = connect(s, servinfo->ai_addr, servinfo->ai_addrlen);
	if(con == -1){
		fprintf(stderr, "connect failed");
		return 3;
	}
	//send one character at a time, not the most efficient, but technichally follows the specifications
	while(1){
		c = getchar( );
		if(c == -1) break;
		send(s, &c, 1, 0);
	}
	close(s);
	  
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
