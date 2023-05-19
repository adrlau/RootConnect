#ifndef MESH_HPP
#define MESH_HPP

#include <iostream>
#include <string>
#include <vector>
#include <list>


class Mesh {
public:

    struct Node {
        std::string publicKey;
        std::string address;

        std::string bindAddress(){
            //return address until the first :
            return address.substr(0, address.find(":"));
        }

        int bindPort(){
            //return the port after the first :
            return std::stoi(address.substr(address.find(":") + 1));
        }
    };

    struct Edge {
        Mesh::Node source;
        Mesh::Node target;
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
    std::vector<Mesh::Node> nodes;
    std::vector<Mesh::Edge> edges;
    bool dfs(const Mesh::Node& currentNode, const Mesh::Node& target, std::vector<Mesh::Node>& path, std::list<Mesh::Node>& visitedNodes);
};

#endif // MESH_HPP
