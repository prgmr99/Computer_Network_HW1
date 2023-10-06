#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 7891
#define MAX_CLIENTS 10

int clientSockets[MAX_CLIENTS];
int numClients = 0;

void *handleClient(void *arg) {
    int clientSocket = *((int *)arg);
    char buffer[1024];
    int bytesRead;

    while (1) {
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            // 클라이언트 연결이 끊기면 스레드 종료
            close(clientSocket);
            break;
        }

        // 받은 메시지를 모든 클라이언트에게 브로드캐스트
        for (int i = 0; i < numClients; i++) {
            if (clientSockets[i] != -1 && clientSockets[i] != clientSocket) {
                send(clientSockets[i], buffer, bytesRead, 0);
            }
        }
    }

    // 클라이언트를 목록에서 제거
    for (int i = 0; i < numClients; i++) {
        if (clientSockets[i] == clientSocket) {
            clientSockets[i] = -1;
            numClients--;
            break;
        }
    }

    pthread_exit(NULL);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        clientSockets[i] = -1;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);

    printf("서버 대기 중...\n");

    while (1) {
        addr_size = sizeof(clientAddr);
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addr_size);

        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clientSockets[i] == -1) {
                clientSockets[i] = clientSocket;
                numClients++;
                break;
            }
        }

        // 클라이언트를 핸들링할 스레드를 생성
        pthread_t thread;
        pthread_create(&thread, NULL, handleClient, (void *)&clientSocket);
    }

    return 0;
}

