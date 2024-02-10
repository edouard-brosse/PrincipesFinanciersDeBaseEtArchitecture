#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

#define TCP_PORT 8080
#define UDP_PORT 8081
#define BUFFER_SIZE 1024

void handleTCP() {
    int sockfd, newSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("TCP socket failed");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(TCP_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("TCP bind failed");
        exit(EXIT_FAILURE);
    }

    listen(sockfd, 5);

    while (true) {
        addr_size = sizeof(clientAddr);
        newSocket = accept(sockfd, (struct sockaddr*)&clientAddr, &addr_size);
        read(newSocket, buffer, BUFFER_SIZE);
        std::cout << "TCP received: " << buffer << std::endl;
        write(newSocket, "coucou", 6);
        close(newSocket);
    }
}

void handleUDP() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_size;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("UDP socket failed");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(UDP_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("UDP bind failed");
        exit(EXIT_FAILURE);
    }

    while (true) {
        addr_size = sizeof(clientAddr);
        recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddr, &addr_size);
        std::cout << "UDP received: " << buffer << std::endl;
        sendto(sockfd, "coucou", 6, 0, (struct sockaddr*)&clientAddr, addr_size);
    }
}

int main() {
    std::thread tcpThread(handleTCP);
    std::thread udpThread(handleUDP);

    tcpThread.join();
    udpThread.join();

    return 0;
}
