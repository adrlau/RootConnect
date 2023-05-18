#include "mesh.hpp"
#include <iostream>
#include <vector>

int main() {
    Mesh mesh1;
    Mesh mesh2;

    Mesh::Node node1 = mesh1.addNode("127.0.0.1:8080", "keyA");
    Mesh::Node node2 = mesh1.addNode("127.0.0.1:8081", "keyB");
    Mesh::Node node3 = mesh2.addNode("127.0.0.1:8082", "keyC");
    Mesh::Node node4 = mesh2.addNode("127.0.0.1:8083", "keyD");

    mesh1.addEdge(node1, node2);
    mesh2.addEdge(node3, node4);

    std::cout << "Mesh 1: " << std::endl;
    mesh1.printMesh();
    std::cout << "Mesh 2: " << std::endl;
    mesh2.printMesh();

    // Merge the two meshes
    mesh1.mergeMesh(mesh2);

    //add a edge between node2 and node3
    mesh1.addEdge(node2, node3);
    
    std::cout << "Merged Mesh: " << std::endl;
    mesh1.printMesh();


    std::vector<Mesh::Node> randomPath = mesh1.findPath(node1, node4);

    std::cout << "Shortest Path: ";
    for (const auto& node : randomPath) {
        std::cout << node.publicKey << " -> ";
    }
    std::cout << std::endl;

    return 0;
}
