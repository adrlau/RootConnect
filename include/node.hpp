#ifndef NODE_HPP
#define NODE_HPP

#include <string>

class Node {
private:
    std::string address;
    std::string publicKey;

public:
    Node(const std::string& nodeAddress, const std::string& nodeEncryptionKey);

    std::string getID() const;

    std::string getAddress() const;

    std::string getPublicKey() const;
};

#endif // NODE_HPP
