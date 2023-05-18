#pragma once
#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>
#include "node.hpp"
#include "edge.hpp"

class Mesh {
private:
    std::vector<Node*> nodes;
    std::vector<Edge*> edges;

public:
    ~Mesh();

    Node* createNode(const std::string& nodeAddress, const std::string& nodeEncryptionKey);

    void createEdge(Node* source, Node* target);

    Node* getRandomNeighbor(Node* node); // Helper function to get a random neighbor node of a given node

    std::vector<Node*> generateRandomPath(Node* startNode, Node* endNode, int numJumps);

    std::vector<Node*> getMesh() const;

    void addMesh(const Mesh& otherMesh);

    void printMesh() const;
};

#endif // MESH_HPP
