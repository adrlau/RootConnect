#include <iostream>

#include "../include/networking.cpp"

int main() {
    // Take input for the address and port to bind to
    std::string address;
    std::cout << "Enter address to bind to (127.0.0.1): ";
    std::getline(std::cin, address);
    if (address.empty()) {
        address = "127.0.0.1"; // Set default to localhost
    }

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

    std::cout << "Listening for messages..." << std::endl;

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

        std::string message;
        std::cout << "Enter message to send: ";
        std::getline(std::cin, message);

        networking.sendMessage(sendAddress, sendPort, message);
    }

    // Wait for some time to receive messages
    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}
