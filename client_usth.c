#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	char buffer[256];
	struct sockaddr_in testaddr[10];
	struct sockaddr_in saddr;
	struct hostent *h;
	int sockfd;
	int n;
	unsigned int port = 8784;
	char s[100];
    
	if (argc > 1) {
		memcpy(s, argv[1], strlen(argv[1]) + 1);
	}
	else {
		printf("Enter hostname: ");
		scanf("%s", s);
	}

	// create the socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error creating socket\n");
		return -1;
	}

	// resolve host address
	if ((h = gethostbyname(s)) == NULL) {
		printf("Unknown host\n");
		close(sockfd);
		return -1;
	}
	
	// init sockaddr
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr = *(struct in_addr *)h->h_addr_list[0];
	saddr.sin_port = htons(port);

	// connect to server
	if (connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		printf("Cannot connect to host\n");
		close(sockfd);
		return -1;
	}

	while (1) {
        	// TODO: add logics to communicate with server
		printf("Client enter message: ");
		bzero(buffer,256);
		fgets(buffer,255,stdin);
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0) 
			error("ERROR writing to socket");
		
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if (n < 0) 
			error("ERROR reading from socket");
		if (n == 0) continue;    
		printf("Received: %s\n",buffer);
	}
	close(sockfd);
}

