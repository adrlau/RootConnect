#include "edge.hpp"
#include "node.hpp"

Edge::Edge(Node* source, Node* target)
    : sourceNode(source), targetNode(target) {}

Node* Edge::getSourceNode() const {
    return sourceNode;
}

Node* Edge::getTargetNode() const {
    return targetNode;
}
