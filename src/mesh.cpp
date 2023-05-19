#include "mesh.hpp"
#include <random>
#include <ctime>

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
    //and add the edge the other way around
    Edge newEdge2;
    newEdge2.source = target;
    newEdge2.target = source;
    edges.push_back(newEdge2);
}

void Mesh::removeEdge(const Mesh::Node& source, const Mesh::Node& target) {
    // Remove the edge from the edges vector
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (it->source.publicKey == source.publicKey && it->target.publicKey == target.publicKey) {
            edges.erase(it);
            break;
        }
    }
    //and remove the edge the other way around
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (it->source.publicKey == target.publicKey && it->target.publicKey == source.publicKey) {
            edges.erase(it);
            break;
        }
    }
}



std::vector<Mesh::Node> Mesh::findPath(const Mesh::Node& source, const Mesh::Node& target) {
    std::vector<Node> prePath;
    std::list<Node> preVisitedNodes;  // Track visited nodes to avoid cycles

    //select a random node from the mesh and dfs to find the path to that node
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, nodes.size() - 1);

    // Generate a random node index
    int count = 0;
    Node random;
    bool foundPrePath = false;
    while (count < 100 && random.publicKey != source.publicKey && random.publicKey != target.publicKey && !foundPrePath)
    {
        int randomNode = dist(gen);
        random = nodes[randomNode];
        //first find the path to a random node to increase the minimum number of hops
        std::cout << "Random node: " << random.publicKey << std::endl;
        foundPrePath = dfs(source, random, prePath, preVisitedNodes);
        if (!foundPrePath)
        {
            prePath.clear();
            preVisitedNodes.clear();
        }
    }

    
    std::vector<Node> path;
    std::list<Node> visitedNodes;  // Track visited nodes to avoid cycles

    // Perform depth-first search
    bool pathFound = dfs(random, target, path, visitedNodes);

    // Combine the two paths
    std::vector<Node> finalpath;
    if (foundPrePath && prePath.size() > 0)
    {
        for (size_t i = 0; i < prePath.size()-1; i++) {
            finalpath.push_back(prePath[i]);
        }
    }
    if (pathFound)
    {
        for (size_t i = 0; i < path.size(); i++) {
            finalpath.push_back(path[i]);
        }
    }
    

    if (pathFound) {
        // path.push_back(target); //removed because it was adding the target node twice
        return finalpath;
    } else {
        return std::vector<Node>();  // No path exists from source to target
    }
}

bool Mesh::dfs(const Mesh::Node& currentNode, const Mesh::Node& target, std::vector<Mesh::Node>& path, std::list<Mesh::Node>& visitedNodes) {
    path.push_back(currentNode);
    visitedNodes.push_back(currentNode);

    if (currentNode.publicKey == target.publicKey) {
        return true;  // Found the target node
    }

    for (const auto& edge : edges) {
        if (edge.source.publicKey == currentNode.publicKey) {
            bool alreadyVisited = false;
            for (const auto& visitedNode : visitedNodes) {
                if (visitedNode.publicKey == edge.target.publicKey) {
                    alreadyVisited = true;
                    break;
                }
            }
            if (!alreadyVisited) {
                bool pathFound = dfs(edge.target, target, path, visitedNodes);
                if (pathFound) {
                    return true;  // Path to the target found
                }
            }
        }
    }

    path.pop_back();
    visitedNodes.pop_back();
    return false;  // No path found from the current node
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
