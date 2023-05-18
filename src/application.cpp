#include <iostream>
#include "networking.hpp"
#include "message.hpp"

class Application {

public:
    Application() {main();}

    int main() {

        // Take input for the address to bind to
        std::string address;
        std::cout << "Enter address to bind to (127.0.0.1): ";
        std::getline(std::cin, address);
        if (address.empty()) {
            address = "127.0.0.1"; // Set default to localhost
        }

        // Take input for the port to bind to
        std::string portInput;
        int port;
        std::cout << "Enter port to bind to (8080): ";
        std::getline(std::cin, portInput);
        if (portInput.empty()) {
            port = 8080; // Set default port
        } else {
            port = std::stoi(portInput);
        }

        Networking networking(address, port);
        networking.startListeningThread();
        std::cout << "Started Listening for messages..." << std::endl;

        // Main loop
        bool running = true;
        while (running) {
            // Take input for where to send to
            std::string sendAddress;
            std::cout << "Enter address to send to (default: 127.0.0.1, enter 'q' to quit): ";
            std::getline(std::cin, sendAddress);
            if (sendAddress.empty()) {
                sendAddress = "127.0.0.1"; // Set default to localhost
            }
            if (sendAddress == "q") {
                running = false; // Quit the loop if 'q' is entered
                continue;
            }

            std::string sendPortInput;
            int sendPort;
            std::cout << "Enter port to send to (8080): ";
            std::getline(std::cin, sendPortInput);
            if (sendPortInput.empty()) {
                sendPort = 8080; // Set default port
            } else {
                sendPort = std::stoi(sendPortInput);
            }

            std::string messageContent;
            std::cout << "Enter message content: ";
            std::getline(std::cin, messageContent);

            // Create a Message object with the next address and content
            Message message(sendAddress, messageContent);

            // Send the message
            networking.sendMessage(sendAddress, sendPort, message.toString());
        }

        // Wait for some time to receive messages
        std::this_thread::sleep_for(std::chrono::seconds(5));

        return 0;
    }

};