#include <iostream>
#include "message.hpp"

Message::Message(const std::string& n, const std::string& c)
    : nextAddress(n), content(c) {}

// Message::Message(const std::string& s) {
//     nextAddress = s.substr(s.find("Next-Destination: ") + 17, s.find("Content:") - s.find("Next-Destination:") - 17);
//     content = s.substr(s.find("Content:") + 8, s.find("Padding:") - s.find("Content:") - 8);
// }

std::string Message::getContent() {
    return content;
}

void Message::setNextAddress(const std::string& n) {
    nextAddress = n;
}

void Message::setContent(const std::string& c) {
    content = c;
}

std::string Message::getNextAddress() const {
    return nextAddress;
}

int Message::getNextPort(const std::string& nextAddress) {
    size_t colonPos = nextAddress.find(':');
    if (colonPos != std::string::npos) {
        std::string portStr = nextAddress.substr(colonPos + 1);
        try {
            int port = std::stoi(portStr);
            return port;
        } catch (const std::exception& e) {
            std::cerr << "Error converting port to integer: " << e.what() << std::endl;
        }
    }
    return -1;  // or any other value indicating failure to parse the port
}

std::string Message::getNextAddress(const std::string& nextAddress) {
    size_t colonPos = nextAddress.find(':');
    if (colonPos != std::string::npos) {
        std::string address = nextAddress.substr(0, colonPos);
        return address;
    }
    return "";  // or any other value indicating failure to parse the address
}

bool Message::isDestination() {
    return nextAddress == "NULL";
}

std::string Message::toString() const {
    std::string result = "\n";
    result += "Next-Destination: " + nextAddress + "\n";
    result += "Content: " + content + "\n";
    return result;
}
