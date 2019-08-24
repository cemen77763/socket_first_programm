#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>



#define MY_SOCK_PATH "./"

#define handle_error(msg)\
 do { perror(msg); exit(EXIT_FAILURE); } while(0);

int main(int agrc, char *argv[]){
	int sfd, cfd;
	char buff[255];
	struct sockaddr_in my_addr, peer_addr;
	socklen_t peer_addr_size;

	sfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sfd == -1)
		handle_error("socket");

	memset(&my_addr, 0, sizeof(struct sockaddr_in));

	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	my_addr.sin_port = htons(5555);

	if (bind(sfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_in)) == -1)
		handle_error("bind");

	if (listen(sfd, 5) == -1)
		handle_error("listen");

	cfd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_size);
	if (cfd == -1)
		handle_error("accept");

	recv(cfd, buff, 255, 0);

	printf("I receive %s\n", buff);

	buff[0] = 'H'; buff[1] = 'i'; buff[2] = '!'; buff[3] = '\0';

	send(cfd, buff, 255, 0);




	close(sfd);
	exit(EXIT_SUCCESS);
}