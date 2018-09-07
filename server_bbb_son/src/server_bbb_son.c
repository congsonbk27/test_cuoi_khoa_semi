/*
 ============================================================================
 Name        : server_bbb_son.c
 Author      : son
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int control_led(int led, int status) {
	char cmd[100];
	sprintf(cmd, "cd /sys/class/leds/beaglebone:green:usr%d/", led);
	if (status == 1) {
		system(cmd);
		system("echo '1' > brightness");
	} else {
		system(cmd);
		system("echo '0' > brightness");
	}
	return 0;
}

int main(int argc, char *argv[]) {
	int socket_desc, client_sock, c, read_size;
	struct sockaddr_in server, client;
	char client_message[30];

	//Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1) {
		printf("Could not create socket");
	}
	puts("Socket created");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	//Bind
	if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");

	//Listen
	listen(socket_desc, 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);

	//accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr *) &client,
			(socklen_t*) &c);
	if (client_sock < 0) {
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");

	//Receive a message from client
	while (1) {
		read_size = recv(client_sock, client_message, 30, 0);
		if (read_size > 0)
		{
			//Send the message back to client
			printf("%s\n", client_message);
			write(client_sock, client_message, strlen(client_message));

			if (strcmp(client_message, "./clientLed 3 0") == NULL) {
				control_led(3, 0);
			} else if (strcmp(client_message, "./clientLed 3 1") == NULL) {
				control_led(3, 1);
			}

			else if (strcmp(client_message, "./clientLed 2 0") == NULL) {
				control_led(2, 0);
			} else if (strcmp(client_message, "./clientLed 2 1") == NULL) {
				control_led(2, 1);
			}

			else if (strcmp(client_message, "./clientLed 1 0") == NULL) {
				control_led(1, 0);
			} else if (strcmp(client_message, "./clientLed 1 1") == NULL) {
				control_led(1, 1);
			}

			else if (strcmp(client_message, "./clientLed 0 0") == NULL) {
				control_led(0, 0);
			} else if (strcmp(client_message, "./clientLed 0 1") == NULL) {
				control_led(0, 1);
			}
		}
		memset(client_message, 0, 30);
	}

	if (read_size == 0) {
		puts("Client disconnected");
		fflush(stdout);
	} else if (read_size == -1) {
		perror("recv failed");
	}

	close(socket_desc);
	close(client_sock);
	return 0;
}

