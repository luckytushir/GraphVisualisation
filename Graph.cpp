#include "Graph.h"

void Graph::addNode(const sf::Vector2u& position, int data) {
    nodes.push_back({ position, data });
}

void Graph::addNode(const sf::Vector2u& position) {
    addNode(position, 0);
}

void Graph::addEdge(int from, int to, bool directed) {
    if (from >= 0 && from < static_cast<int>(nodes.size()) &&
        to >= 0 && to < static_cast<int>(nodes.size()))
    {
        edges.push_back({ from, to, directed });
        if (!directed) {
            edges.push_back({ to, from, directed });
        }
    }
}

void Graph::clear() {
    nodes.clear();
    edges.clear();
}

int Graph::getNodeCount() const {
    return static_cast<int>(nodes.size());
}

int Graph::getEdgeCount() const {
    return static_cast<int>(edges.size());
}

// No weights in this version; return -1 for all pairs
int Graph::getWeight(int /*from*/, int /*to*/) const {
    return -1;
}

const std::vector<Node>& Graph::getNodes() const {
    return nodes;
}

const std::vector<Edge>& Graph::getEdges() const {
    return edges;
}
