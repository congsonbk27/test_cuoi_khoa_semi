#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int sock;
	struct sockaddr_in server;
	char message[30], server_reply[30];

	//Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");
	char * ipaddr = "192.186.7.2";
	server.sin_addr.s_addr = inet_addr(ipaddr);
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		perror("connect failed. Error");
		return 1;
	}
	puts("Connected\n");
	while (1) {
		printf("Enter message : ");
		scanf("%s", message);
		//Receive a reply from the server
		if (recv(sock, server_reply, 30, 0) < 0) {
			puts("recv failed");
			break;
		}

		//Send some data
		if (send(sock, message, strlen(message), 0) < 0) {
			puts("Send failed");
			return 1;
		}

		//Receive a reply from the server
		if (recv(sock, server_reply, 30, 0) < 0) {
			puts("recv failed");
			break;
		}

		puts("Server reply :");
		puts(server_reply);
	}

	close(sock);
	return 0;
}
