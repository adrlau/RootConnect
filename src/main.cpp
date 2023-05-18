#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

#include "node.hpp"
#include "edge.hpp"
#include "mesh.hpp"

int main() {
    // Create the first mesh
    Mesh mesh1;
    Node* node1 = mesh1.createNode("192.168.0.1", "keyA");
    Node* node2 = mesh1.createNode("192.168.0.2", "keyB");
    mesh1.createEdge(node1, node2);

    // Print the first mesh
    std::cout << "Mesh 1:" << std::endl;
    mesh1.printMesh();

    // Create the second mesh
    Mesh mesh2;
    Node* node3 = mesh2.createNode("192.168.0.3", "keyC");
    Node* node4 = mesh2.createNode("192.168.0.4", "keyD");
    mesh2.createEdge(node3, node4);

    // Print the second mesh
    std::cout << "Mesh 2:" << std::endl;
    mesh2.printMesh();

    // Add mesh2 to mesh1
    mesh1.addMesh(mesh2);
    mesh1.createEdge(node2, node3);

    // Print the combined mesh
    std::cout << "Combined Mesh:" << std::endl;
    mesh1.printMesh();

    // Get the nodes of the combined mesh
    std::vector<Node*> combinedNodes = mesh1.getMesh();
    std::cout << "Combined Mesh Nodes:" << std::endl;
    for (Node* node : combinedNodes) {
        std::cout << "Node ID: " << node->getID() << ", Address: " << node->getAddress() << ", Public Key: " << node->getPublicKey() << std::endl;
    }

    // Generate a random path in the combined mesh
    std::cout << "Generating random path..." << std::endl;
    std::vector<Node*> randomPath = mesh1.generateRandomPath(node1, node4, 3);
    std::cout << "Random Path:" << std::endl;
    for (Node* node : randomPath) {
        std::cout << "Node ID: " << node->getID() << std::endl;
    }

    return 0;
}
