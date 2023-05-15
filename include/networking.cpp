#include <iostream>
#include <string>
#include <thread>

class Networking {
private:
    std::string ipAddress;
    int port;

public:
    Networking(const std::string& ip, int p) : ipAddress(ip), port(p) {}

    void sendMessage(const std::string& message) {
        // Implement sending message over the network
        // Example: send(message, ipAddress, port)
        std::cout << "Message sent: " << message << std::endl;
    }

    void listenForMessages() {
        // Implement listening for incoming messages over the network
        // Example: while (true) { message = receive(); processMessage(message); }
        std::cout << "Listening for messages..." << std::endl;
    }

    void startListeningThread() {
        std::thread listenerThread(&Networking::listenForMessages, this);
        listenerThread.detach();
    }
};