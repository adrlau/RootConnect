#include "networking.hpp"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

Networking::Networking(const std::string& ip, int p) : ipAddress(ip), port(p), socketDescriptor(-1) {}

Networking::Networking() {}

void Networking::sendMessage(const std::string& address, int port, const std::string& message) {
    std::thread sendThread([this, address, port, message]() {
        int sock = createSocket();
        if (sock == -1) {
            std::cout << "Failed to create socket" << std::endl;
            return;
        }

        if (connectToServer(sock, address, port)) {
            ssize_t bytesSent = send(sock, message.c_str(), message.length(), 0);
            if (bytesSent == -1) {
                std::cout << "Failed to send message" << std::endl;
            }

            close(sock);
        } else {
            std::cout << "Failed to connect to server" << std::endl;
            close(sock);
        }
    });

    sendThread.detach();

    // Wait for the send operation to complete or reach the timeout
    std::this_thread::sleep_for(std::chrono::seconds(timeout));
}

void Networking::listenForMessages() {
    int sock = createSocket();
    if (sock == -1) {
        std::cout << "Failed to create socket" << std::endl;
        return;
    }

    if (bindSocket(sock) && listenForConnections(sock)) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);

        while (true) {
            int clientSocket = accept(sock, (struct sockaddr*)&clientAddress, &clientAddressLength);
            if (clientSocket < 0) {
                std::cout << "Failed to accept client connection" << std::endl;
                continue;
            }
            char buffer[1024];
            memset(buffer, 0, sizeof(buffer));
            ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesRead > 0) {
                std::string receivedMessage(buffer);

                // TODO: if a message was received and it should be relayed, relay it to the next address

                std::cout << "Received message: " << receivedMessage << std::endl;
            }
            close(clientSocket);
        }
    } else {
        std::cout << "Failed to bind or listen for connections" << std::endl;
        close(sock);
    }
}

void Networking::startListeningThread() {
    std::thread listenerThread(&Networking::listenForMessages, this);
    listenerThread.detach();
}

int Networking::createSocket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
    std::cout << "Failed to create socket" << std::endl;
    }
    return sock;
}

bool Networking::connectToServer(int sock, const std::string& address, int port) {
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    if (inet_pton(AF_INET, address.c_str(), &(serverAddress.sin_addr)) <= 0) {
        std::cout << "Invalid IP address" << std::endl;
        return false;
    }
    if (connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cout << "Connection failed" << std::endl;
        return false;
    }
    return true;
}

bool Networking::bindSocket(int sock) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cout << "Binding failed" << std::endl;
        return false;
    }
    return true;
}

bool Networking::listenForConnections(int sock) {
    if (listen(sock, 5) < 0) {
        std::cout << "Failed to listen for connections" << std::endl;
        return false;
    }
    return true;
}

