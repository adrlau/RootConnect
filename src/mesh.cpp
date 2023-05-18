#include "mesh.hpp"

Mesh::Mesh() {}

Mesh::Node Mesh::addNode(const std::string& address, const std::string& publicKey) {
    Node newNode;
    newNode.address = address;
    newNode.publicKey = publicKey;
    nodes.push_back(newNode);
    return newNode;
}

void Mesh::removeNode(const Node& node) {
    // Remove the node from the nodes vector
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (it->publicKey == node.publicKey) {
            nodes.erase(it);
            break;
        }
    }

    // Remove the edges associated with the removed node
    for (auto it = edges.begin(); it != edges.end();) {
        if (it->source.publicKey == node.publicKey || it->target.publicKey == node.publicKey) {
            it = edges.erase(it);
        } else {
            ++it;
        }
    }
}

void Mesh::addEdge(const Mesh::Node& source, const Mesh::Node& target) {
    Edge newEdge;
    newEdge.source = source;
    newEdge.target = target;
    edges.push_back(newEdge);
}

void Mesh::removeEdge(const Mesh::Node& source, const Mesh::Node& target) {
    // Remove the edge from the edges vector
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (it->source.publicKey == source.publicKey && it->target.publicKey == target.publicKey) {
            edges.erase(it);
            break;
        }
    }
}

std::vector<Mesh::Node> Mesh::findPath(const Mesh::Node& source, const Mesh::Node& target) {
    std::vector<Node> path;
    path.push_back(source);

    // Find the path from source to target
    Node currentNode = source;
    while (currentNode.publicKey != target.publicKey) {
        bool foundNextNode = false;
        for (const auto& edge : edges) {
            if (edge.source.publicKey == currentNode.publicKey) {
                path.push_back(edge.target);
                currentNode = edge.target;
                foundNextNode = true;
                break;
            }
        }

        if (!foundNextNode) {
            // No path exists from source to target
            return std::vector<Node>();
        }
    }

    return path;
}

void Mesh::mergeMesh(const Mesh otherMesh) {
    // Merge the nodes and edges from the otherMesh
    nodes.insert(nodes.end(), otherMesh.nodes.begin(), otherMesh.nodes.end());
    edges.insert(edges.end(), otherMesh.edges.begin(), otherMesh.edges.end());
}

std::vector<Mesh::Node> Mesh::getNodes() const {
    return nodes;
}

Mesh::Node Mesh::getNode(const std::string& publicKey) const {
    for (const auto& node : nodes) {
        if (node.publicKey == publicKey) {
            return node;
        }
    }
    // Return an empty node if the specified publicKey is not found
    return Node();
}

void Mesh::printMesh() {
    std::cout << "Nodes:\n";
    for (const auto& node : nodes) {
        std::cout << "Public Key: " << node.publicKey << ", Address: " << node.address << '\n';
    }

    std::cout << "Edges:\n";
    for (const auto& edge : edges) {
        std::cout << "Source: " << edge.source.publicKey << ", Target: " << edge.target.publicKey << '\n';
    }
}
