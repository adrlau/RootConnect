#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>

#include "mesh.hpp"
#include "node.hpp"
#include "edge.hpp"

Mesh::~Mesh() {
    // Clean up dynamically allocated nodes and edges
    for (Node* node : nodes) {
        delete node;
    }
    for (Edge* edge : edges) {
        delete edge;
    }
}

Node* Mesh::createNode(const std::string& nodeAddress, const std::string& nodeEncryptionKey) {
    Node* node = new Node(nodeAddress, nodeEncryptionKey);
    nodes.push_back(node);
    return node;
}

void Mesh::createEdge(Node* source, Node* target) {
    Edge* edge = new Edge(source, target);
    edges.push_back(edge);
}


// Get a random neighbor of a given node
Node* Mesh::getRandomNeighbor(Node* node) {
    std::vector<Node*> neighbors;
    for (Edge* edge : this->edges) {
        if (edge->getSourceNode() == node) {
            neighbors.push_back(edge->getTargetNode());
        } else if (edge->getTargetNode() == node) {
            neighbors.push_back(edge->getSourceNode());
        }
    }

    if (!neighbors.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dist(0, neighbors.size() - 1);
        return neighbors[dist(gen)];
    }

    return nullptr;
}


// Generate a random path from one node to another node with a minimum number of n jumps
std::vector<Node*> Mesh::generateRandomPath(Node* start, Node* end, int n) {
        std::vector<Node*> path;
        std::unordered_set<Node*> visited;
        path.push_back(start);
        visited.insert(start);

        while (path.size() - 1 < n || path.back() != end) {
            Node* current = path.back();
            Node* next = getRandomNeighbor(current);

            if (!next) {
                // No more available neighbors, backtrack
                if (path.size() <= 1) {
                    // Reached a dead end, cannot reach the target node
                    return {};
                }
                path.pop_back();
            } else {
                if (visited.find(next) != visited.end()) {
                    // Avoid revisiting nodes to prevent cycles
                    continue;
                }
                path.push_back(next);
                visited.insert(next);
            }
        }
        return path;
}



std::vector<Node*> Mesh::getMesh() const {
return nodes;
}

void Mesh::addMesh(const Mesh& otherMesh) {
    // Add nodes from otherMesh
    for (Node* node : otherMesh.nodes) {
    // Check if the node already exists in the current mesh
    auto it = std::find_if(nodes.begin(), nodes.end(), [&](const Node* n) {
    return n->getID() == node->getID();
    });
        if (it == nodes.end()) {
            // Node doesn't exist in the current mesh, so add it
            createNode(node->getAddress(), node->getPublicKey());
        }
    }

    // Add edges from otherMesh
    for (Edge* edge : otherMesh.edges) {
        Node* source = nullptr;
        Node* target = nullptr;

        // Find the corresponding source node in the current mesh
        auto sourceIt = std::find_if(nodes.begin(), nodes.end(), [&](const Node* n) {
            return n->getID() == edge->getSourceNode()->getID();
        });

        if (sourceIt != nodes.end()) {
            source = *sourceIt;
        }

        // Find the corresponding target node in the current mesh
        auto targetIt = std::find_if(nodes.begin(), nodes.end(), [&](const Node* n) {
            return n->getID() == edge->getTargetNode()->getID();
        });

        if (targetIt != nodes.end()) {
            target = *targetIt;
        }

        if (source && target) {
            // Both source and target nodes exist, so create the edge
            createEdge(source, target);
        }
    }
}

void Mesh::printMesh() const {
    for (Edge* edge : edges) {
    std::cout << "Edge: " << edge->getSourceNode()->getID() << " <-> " << edge->getTargetNode()->getID() << std::endl;
    }
}
