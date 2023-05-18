#include "node.hpp"


Node::Node(const std::string& nodeAddress, const std::string& nodeEncryptionKey)
    : address(nodeAddress), publicKey(nodeEncryptionKey) {}

std::string Node::getID() const {
    return publicKey;
}

std::string Node::getAddress() const {
    return address;
}

std::string Node::getPublicKey() const {
    return publicKey;
}
