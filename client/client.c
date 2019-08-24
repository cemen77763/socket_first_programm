#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define handle_error(msg)\
 do { perror(msg); exit(EXIT_FAILURE); } while(0);

int main(int agrc, char *argv[]){
	int cfd;
	char buff[255];
	struct sockaddr_in peer_addr;

	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if (cfd == -1)
		handle_error("socket");

	memset(&peer_addr, 0, sizeof(struct sockaddr_in));
	peer_addr.sin_family = AF_INET;
	peer_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	peer_addr.sin_port = htons(5555);

	if (connect(cfd, (struct sockaddr *) &peer_addr, sizeof(struct sockaddr_in)) == -1)
		handle_error("connect");

	buff[0] = 'H'; buff[1] = 'e'; buff[2] = 'l'; buff[3] = 'l'; buff[4] = 'o'; buff[5] = '!'; buff[6] = '\0';

	send(cfd, buff, sizeof(buff), 0);

	recv(cfd, buff, sizeof(buff), 0);

	printf("I receive %s\n", buff);

	close(cfd);
	exit(EXIT_SUCCESS);
}