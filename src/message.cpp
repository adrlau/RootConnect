#include <iostream>
#include <vector>
#include <algorithm>
#include "message.hpp"
#include "mesh.hpp"
#include "encryption.hpp"

Message::Message(const std::string& n, const std::string& c)
    : nextAddress(n), content(c), encrypted(false) {}

//generate a message from to string
Message::Message(const std::string& sInn) {

    //remove \n from the absolite beginning of the string and the absolute end of the string, not any other \n
    std::string s = sInn;
    if (s[0] == '\n') {
        s = s.substr(1);
    }
    
    // std::cout << std::endl << "s: " << s << std::endl;

    if (s.empty()) {
        std::cout << "empty string" << std::endl;
        return;
    }
    if (s[s.size() - 1] == '\n') {
        s = s.substr(0, s.find_last_of('\n'));
    }
    std::cout << std::endl << "s: " << s << std::endl;

    //split the string into two parts by the first line break
    char targetByte = '\n';
    size_t lineBreakPos = s.find(targetByte);

    if (lineBreakPos != std::string::npos) {
        nextAddress = s.substr(0, lineBreakPos);
        //remove "nextAddress:"
        nextAddress = nextAddress.substr(nextAddress.find(':') + 1);
        content = s.substr(lineBreakPos + 1);
        //remove "content:"
        content = content.substr(content.find(':') + 1);
    }

}


void Message::setContent(const std::string& c) {
    content = c;
}

void Message::setNextAddress(const std::string& n) {
    nextAddress = n;
}

std::string Message::getContent() {
    return content;
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
    return -1;  //or any other value indicating failure to parse the port
}

std::string Message::getNextAddress() const {
    return nextAddress.substr(0, nextAddress.find(':'));
}
std::string Message::getNextAddressFull() const {
    return nextAddress;
}

bool Message::isDestination() {
    return nextAddress == "NULL";
}

bool Message::isEncrypted() {
    return encrypted;
}

void Message::encrypt(std::string publicKey) {
    content = Encryption::encrypt(content, publicKey);
    encrypted = true;
}

Message Message::encode(std::vector<Mesh::Node> path) const {
    //get a path of nodes to encode the message for with the onion style encryption
    //the first node in the path is the start node and the last node is the destination so we need to reverse the path
    std::reverse(path.begin(), path.end());
    //create the first message to the final destination
    Message message("NULL", content);
    //for each node in the path set the content as an the previous message encrypted and set the next address as the previous node in the path
    for (size_t i = 1; i < path.size(); i++) {
        message.setContent(Encryption::encrypt(message.toString(), path[i-1].publicKey));
        message.setNextAddress(path[i - 1].address);
    }
    //return the final message
    return message;
}

std::string Message::decode(std::string privateKey) {
    //first decrypt the content of the message
    std::string content = Encryption::decrypt(this->content, privateKey);
    if (isDestination()) {
        std::cout << "test" << std::endl;
        return content;
    }
    //if this is the final destination then return the content
    //create a message from the string
    Message message = Message(content);
    //set the next address as the next address of the message
    this->nextAddress = message.getNextAddress();
    this->content = message.getContent();
    return this->toString();
}

std::string Message::toString() const {
    std::string result = "\n";
    result += "Next-Destination:" + nextAddress + "\n";
    result += "Content:" + content;
    return result;
}

void Message::print() const {
    std::cout << toString();
}
