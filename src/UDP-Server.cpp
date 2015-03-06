//============================================================================
// Name        : UDP-Server.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <iostream>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

#define PORT 1234

#define MAXDATASIZE 100

int main() {
	int sockfd, num;
	struct sockaddr_in server;
	struct sockaddr_in client;
	socklen_t addrlen;
	char buf[MAXDATASIZE];

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket() error.");
		return 1;
	}

	bzero(&server, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr *) &server, sizeof(server)) == -1) {
		cout << server.sin_addr.s_addr << endl;
		perror("bind() error");
		return 1;
	}
	cout << "bind finish" << endl;
	addrlen = sizeof(client);

	while (1) {
		num = recvfrom(sockfd, buf, MAXDATASIZE, 0, (struct sockaddr *) &client,
				&addrlen);
		if (num < 0) {
			perror("recvfrom() error");
			return 1;
		}
		buf[num] = '\0';
		cout << buf << endl;
		printf("Client's ip is %s,port is %d\n", inet_ntoa(client.sin_addr),
				htons(client.sin_port));

		sendto(sockfd, "WELCOME!\n", 8, 0, (struct sockaddr *) &client,
				addrlen);
	}

	close(sockfd);
	return 0;
}
