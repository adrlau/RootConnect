#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <string>
#include <vector>


class Mesh {
public:
    struct Node {
        std::string publicKey;
        std::string address;
    };



    Mesh();

    Mesh::Node addNode(const std::string& address, const std::string& publicKey);
    void removeNode(const Node& node);
    void addEdge(const Mesh::Node& source, const Mesh::Node& target);
    void removeEdge(const Mesh::Node& source, const Mesh::Node& target);

    std::vector<Mesh::Node> findPath(const Mesh::Node& source, const Mesh::Node& target);
    void mergeMesh(const Mesh otherMesh);
    std::vector<Node> getNodes() const;
    Mesh::Node getNode(const std::string& publicKey) const;
    void printMesh();

private:
    struct Edge {
        Mesh::Node source;
        Mesh::Node target;
    };

    std::vector<Mesh::Node> nodes;
    std::vector<Mesh::Edge> edges;
};

#endif // MESH_HPP
