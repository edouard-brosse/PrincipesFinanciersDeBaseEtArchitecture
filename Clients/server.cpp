#include <thread>
#include <map>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <functional>
#include "../Back/OrderBook.h"

#define TCP_PORT 7799
#define UDP_PORT 7799
#define BUFFER_SIZE 1024

std::map<int, std::string> socketIdMap;
std::map<std::string, int> connectedClients;
std::map<std::string, std::string> credentialsMap;
std::map<std::string, std::string> idMap;
std::map<std::string, int> clientUDPSockets;
int clientID = 0;

void handleTCPClient(int clientSocket, struct sockaddr_in clientAddr) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    read(clientSocket, buffer, BUFFER_SIZE);
    std::string message(buffer);
    std::string command;
    std::string credentials;
    if (message.find(" ") != std::string::npos) {
        command = message.substr(0, message.find(" "));
        credentials = message.substr(message.find(" ") + 1);
    } else {
        command = message;
    }
    if (command == "register") {
        std::string username = credentials.substr(0, credentials.find(":"));
        std::string password = credentials.substr(credentials.find(":") + 1);
        if (credentialsMap.find(username) != credentialsMap.end()) {
            std::string response = "Username already exists";
            write(clientSocket, response.c_str(), response.size());
        } else {
            credentialsMap[username] = password;
            std::string id = std::to_string(++clientID);
            idMap[username] = id;
            connectedClients[id] = clientSocket;
            socketIdMap[clientSocket] = id;
            int udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
            clientUDPSockets[id] = udpSocket;
            std::string response = "Your ID is " + id;
            write(clientSocket, response.c_str(), response.size());
        }
    } else if (command == "login") {
        std::string username = credentials.substr(0, credentials.find(":"));
        std::string password = credentials.substr(credentials.find(":") + 1);
        if (credentialsMap[username] == password) {
            std::string id = idMap[username];
            connectedClients[id] = clientSocket;
            socketIdMap[clientSocket] = id;
            int udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
            clientUDPSockets[id] = udpSocket;
            std::string response = "Your ID is " + id;
            write(clientSocket, response.c_str(), response.size());
        } else {
            std::string response = "Wrong login or password";
            write(clientSocket, response.c_str(), response.size());
        }
    } else {
        std::string id = socketIdMap[clientSocket];
        if (command == "exit") {
            std::string response = "You exit and your ID is " + id;
            write(clientSocket, response.c_str(), response.size());
        }  else if (command.rfind("see-my-orders-id-:", 0) == 0) {
    std::string id = command.substr(std::string("see my orders id :").length());
    connectedClients[id] = clientSocket;
    socketIdMap[clientSocket] = id;
    int udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
    clientUDPSockets[id] = udpSocket;

    // REMPLIRE RESPONSE
    std::string response = "le retour sous format string des orders pour l'id :" + id;
    write(clientSocket, response.c_str(), response.size());
} else if (command == "see-all-orders-server") {

            //REMPLIRE RESPONSE
            std::string response = "le retour sous format string des orders generals ";
            write(clientSocket, response.c_str(), response.size());
    } else {
            std::string response = "Unknown command Your ID is " + id;
            write(clientSocket, response.c_str(), response.size());
        }
    }
    close(clientSocket);
}

void handleUDPClient(std::string id) {
    char buffer[BUFFER_SIZE];
    struct sockaddr_in clientAddr;
    socklen_t addr_size = sizeof(clientAddr);
    memset(buffer, 0, sizeof(buffer));
    int udpSocket = clientUDPSockets[id];
    recvfrom(udpSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&clientAddr, &addr_size);
    std::string message(buffer);
    std::string receivedId = message.substr(0, message.find(":"));
    std::string receivedMessage = message.substr(message.find(":") + 1);
    if (connectedClients.count(id) && receivedId == id) {
        if (receivedMessage == "exit") {
            idMap.erase(id);
            return;
        } else {

            //std::string response = "coucou. Your ID is " + id + ". Received message: " + receivedMessage;
            //sendto(udpSocket, response.c_str(), response.size(), 0, (struct sockaddr*)&clientAddr, addr_size);

            //ici requete buy ou sell remove et update qui arrive

        }
    } else {
        sendto(udpSocket, "Not connected or wrong ID", 24, 0, (struct sockaddr*)&clientAddr, addr_size);
    }
}

void handleTCP(int sockfd) {
    struct sockaddr_in clientAddr;
    socklen_t addr_size;
    int newSocket;
    while (true) {
        addr_size = sizeof(clientAddr);
        newSocket = accept(sockfd, (struct sockaddr*)&clientAddr, &addr_size);
        std::thread clientThread(std::bind(handleTCPClient, newSocket, clientAddr));
        clientThread.detach();
    }
}

void handleUDP(std::string id) {
    while (true) {
        handleUDPClient(id);
    }
}

int main() {
    int tcpSocket;
    struct sockaddr_in serverAddr;
    tcpSocket = socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(TCP_PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
    bind(tcpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    if(listen(tcpSocket,50)==0)
        std::cout << "Listening TCP on port " << TCP_PORT << std::endl;
    else
        std::cout << "Error TCP" << std::endl;
    std::thread tcpThread([tcpSocket](){ handleTCP(tcpSocket); });
    tcpThread.join();
    for (auto& pair : connectedClients) {
        std::thread udpThread([pair](){ handleUDP(pair.first); });
        udpThread.detach();
    }
    return 0;
}