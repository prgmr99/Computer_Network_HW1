#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 7891
#define SERVER_IP "127.0.0.1"

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    char message[1024];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

    addr_size = sizeof(serverAddr);
    connect(clientSocket, (struct sockaddr *)&serverAddr, addr_size);

    printf("서버에 연결되었습니다. 채팅을 시작하세요.\n");

    while (1) {
        printf("메시지 입력: ");
        fgets(message, 1024, stdin);
        send(clientSocket, message, strlen(message), 0);

        if (strcmp(message, "exit\n") == 0) {
            printf("채팅을 종료합니다.\n");
            break;
        }

        memset(message, 0, sizeof(message));
        int bytesRead = recv(clientSocket, message, sizeof(message), 0);
        if (bytesRead <= 0) {
            printf("서버와의 연결이 끊어졌습니다.\n");
            break;
        }
        printf("서버: %s", message);
    }

    close(clientSocket);
    return 0;
}

