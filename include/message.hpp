#pragma once
#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

class Message {
public:
    Message(const std::string& n, const std::string& c);
    Message(const std::string& s);
    std::string getContent();
    void setNextAddress(const std::string& n);
    void setContent(const std::string& c);
    std::string getNextAddress() const;
    static int getNextPort(const std::string& nextAddress);
    static std::string getNextAddress(const std::string& nextAddress);
    bool isDestination();
    std::string toString() const;

private:
    std::string nextAddress;
    std::string content;
};
#endif // MESSAGE_HPP
