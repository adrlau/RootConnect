#pragma once
#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include "mesh.hpp"

class Message {
public:
    Message(const std::string& n, const std::string& c);
    Message(const std::string& s);
    
    void setContent(const std::string& c);
    void setNextAddress(const std::string& n);
    
    std::string getContent();

    static int getNextPort(const std::string& nextAddress);
    std::string getNextAddress() const;
    std::string getNextAddressFull() const;

    void encrypt(std::string publicKey);
    Message encode(std::vector<Mesh::Node> path) const;
    std::string decode(std::string privateKey);


    bool isDestination();
    bool isEncrypted();

    std::string toString() const;
    void print() const;

private:
    std::string nextAddress;
    std::string content;
    bool encrypted;
};
#endif // MESSAGE_HPP
