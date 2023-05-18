#ifndef EDGE_HPP
#define EDGE_HPP

class Node; // Forward declaration of the Node class

class Edge {
private:
    Node* sourceNode;
    Node* targetNode;

public:
    Edge(Node* source, Node* target);

    Node* getSourceNode() const;

    Node* getTargetNode() const;
};

#endif // EDGE_HPP
