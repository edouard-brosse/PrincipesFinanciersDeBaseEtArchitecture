#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

#define TCP_PORT 7799
#define UDP_PORT 7799
#define BUFFER_SIZE 1024

std::string id = "";

void tcpClient(const char* serverIP, int serverPort, const char* message) {
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
    connect(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    std::string fullMessage = message;
    if (strcmp(message, "connection") == 0 && !id.empty()) {
        fullMessage += ":" + id;
    }
    char buffer[BUFFER_SIZE];
    write(sock, fullMessage.c_str(), fullMessage.size());
    memset(buffer, 0, sizeof(buffer));
    read(sock, buffer, BUFFER_SIZE);
    std::string response(buffer);
    if (response.find("Your ID is ") != std::string::npos) {
        id = response.substr(response.find("Your ID is ") + 11);
    }
    // gestion du recu du serveur
    std::cout << "Received from server: " << buffer << std::endl;
    close(sock);
}

void udpClient(const char* serverIP, int serverPort, const char* message) {
    int sock = socket(PF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    struct sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(TCP_PORT);
    clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sock, (struct sockaddr*)&clientAddr, sizeof(clientAddr));

    std::string fullMessage = id + ":" + message; 
    char buffer[BUFFER_SIZE];
    socklen_t addr_size = sizeof(serverAddr);
    sendto(sock, fullMessage.c_str(), fullMessage.size(), 0, (struct sockaddr*)&serverAddr, addr_size);
    memset(buffer, 0, sizeof(buffer));
    recvfrom(sock, buffer, BUFFER_SIZE, 0, NULL, NULL);
    // gestion du recu du serveur
    std::cout << "Received from server: " << buffer << std::endl;
    close(sock);
}

int main(int argc, char* argv[]) {
     if (argc > 3) {
        std::string command = argv[2];
        std::string credentials = argv[3];
        tcpClient(argv[1], TCP_PORT, (command + " " + credentials).c_str());
    } else {
        tcpClient(argv[1], TCP_PORT, "new connection");
    }
    while (true) {
        std::string message;
        std::getline(std::cin, message);
        if (message == "bbb") {
            // appler le parser ici 
            udpClient(argv[1], UDP_PORT, message.c_str());
        } else if (message == "exit") {
            tcpClient(argv[1], TCP_PORT, message.c_str());
            break;
        } else {
            tcpClient(argv[1], TCP_PORT, message.c_str());
        }
    }
    return 0;
}

