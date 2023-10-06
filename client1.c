#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdbool.h>

#define BUF_SIZE 1024
#define SERVER_IP 0xC0A801CB
#define PORT_NUM 12457

static pthread_t thr;
static int thr_id;
static bool thr_exit = true;
static char recv_data[BUF_SIZE];
static int client_fd, len, n, n2;
static void *treturn;

void *thread_recv(void *arg);

void thread_start() {
	thr_exit = false;
	thr_id = pthread_create(&thr,NULL,thread_recv,NULL);
}

void thread_stop() {
	thr_exit = true;
	thr_id = pthread_join(thr, &treturn);
}

void *thread_recv(void *arg) {
	while(!thr_exit) {
		if((n = recv(client_fd,recv_data,sizeof(recv_data),0)) == -1) {
			printf("disconnected.\n");
			return (int*)0;
		}
		else if(n > 0) {
			recv_data[n] = '\0';
			printf("\n[서버]: %s\n", recv_data);
		}
	}
	pthread_exit((void*)0);
}

int main(int argc, char *argv[]) {
	struct sockaddr_in client_addr;
	char *IP = SERVER_IP;
	in_port_t PORT = PORT_NUM;
	char chat_data[BUF_SIZE];
	
	/*if(argc != 3) {
		printf("Usage: ./filename [IP] [PORT] \n");
		exit(0);
	}*/
	
	client_fd = socket(PF_INET, SOCK_STREAM,0);
	client_addr.sin_addr.s_addr = htonl(IP);
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(PORT);

	if(connect(client_fd, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1) {
		printf("Can't connect.\n");
		close(client_fd);
		return -1;
	}
	
	while(1) {
		thread_start();
		fgets(chat_data, sizeof(chat_data),stdin);
		send(client_fd, chat_data, sizeof(chat_data),0);
	}
	
	thread_stop();
	close(client_fd);
	return 0;
}

