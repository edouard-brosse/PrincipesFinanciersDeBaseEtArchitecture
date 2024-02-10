#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

void udpClient(const char* serverIP, int serverPort, const char* message) {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[1024] = {0};

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(serverPort);
    servaddr.sin_addr.s_addr = inet_addr(serverIP);

    sendto(sockfd, message, strlen(message), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    std::cout << "Message sent over UDP\n";

    int n, len = sizeof(servaddr);
    n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, ( struct sockaddr *) &servaddr, (socklen_t*)&len);
    buffer[n] = '\0';
    std::cout << "Server response: " << buffer << std::endl;

    close(sockfd);
}

void tcpClient(const char* serverIP, int serverPort, const char* message) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cout << "\n Socket creation error \n";
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serverPort);

    if(inet_pton(AF_INET, serverIP, &serv_addr.sin_addr)<=0) {
        std::cout << "\nInvalid address/ Address not supported \n";
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "\nConnection Failed \n";
        exit(EXIT_FAILURE);
    }

    send(sock, message, strlen(message), 0);
    std::cout << "Message sent over TCP\n";

    read(sock, buffer, 1024);
    std::cout << "Server response: " << buffer << std::endl;

    close(sock);
}

int main(int argc, char const *argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <TCP/UDP> <Server IP> <Port> <Message>\n";
        return 1;
    }

    const char* protocol = argv[1];
    const char* serverIP = argv[2];
    int serverPort = atoi(argv[3]);
    const char* message = argv[4];

    if (strcmp(protocol, "TCP") == 0) {
        tcpClient(serverIP, serverPort, message);
    } else if (strcmp(protocol, "UDP") == 0) {
        udpClient(serverIP, serverPort, message);
    } else {
        std::cerr << "Invalid protocol. Use 'TCP' or 'UDP'.\n";
        return 1;
    }

    return 0;
}

