#ifndef NETWORKING_HPP
#define NETWORKING_HPP

#include <string>
#include <thread>

class Networking {
private:
    std::string ipAddress = "127.0.0.1";
    int port = 8080;
    int socketDescriptor;
    int timeout = 10; // seconds before timeout when waiting to send or receive data

public:
    Networking(const std::string& ip, int p);
    Networking();

    void sendMessage(const std::string& address, int port, const std::string& message);
    void listenForMessages();
    void startListeningThread();

private:
    int createSocket();
    bool connectToServer(int sock, const std::string& address, int port);
    bool bindSocket(int sock);
    bool listenForConnections(int sock);
};

#endif // NETWORKING_HPP
