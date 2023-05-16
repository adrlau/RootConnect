#include <iostream>
#include <string>
#include <vector>

class Node {
private:
    std::string id;
    std::string address;
    std::string encryptionKey; //public key of the node for encryption
    std::vector<Node*> neighbors;

public:
    Node(const std::string& nodeId, const std::string& nodeAddress, const std::string& nodeEncryptionKey)
        : id(nodeId), address(nodeAddress), encryptionKey(nodeEncryptionKey) {}

    std::string getID() const {
        return id;
    }

    std::string getAddress() const {
        return address;
    }

    std::string getEncryptionKey() const {
        return encryptionKey;
    }

    void addNeighbor(Node* neighbor) {
        neighbors.push_back(neighbor);
    }

    void removeNeighbor(Node* neighbor) {
        for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
            if (*it == neighbor) {
                neighbors.erase(it);
                break;
            }
        }
    }

    void printNeighbors() const {
        std::cout << "Neighbors of Node " << id << ":" << std::endl;
        for (const auto& neighbor : neighbors) {
            std::cout << "- Node " << neighbor->getID() << std::endl;
        }
    }
};