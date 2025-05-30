#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

struct Node {
    sf::Vector2u position;
    int data;            // user-stored data value for this node
};

struct Edge {
    int from;
    int to;
    bool directed;
};

class Graph {
public:
    // Add a node at position with given data
    void addNode(const sf::Vector2u& position, int data);
    // Convenience overload: data defaults to 0
    void addNode(const sf::Vector2u& position);

    // Add an edge; if directed==false, also adds the reverse edge
    void addEdge(int from, int to, bool directed);

    // Clear all nodes and edges
    void clear();

    // Utilities for algorithms
    int getNodeCount() const;
    int getEdgeCount() const;
    int getWeight(int from, int to) const;

    // Accessors
    const std::vector<Node>& getNodes() const;
    const std::vector<Edge>& getEdges() const;

private:
    std::vector<Node> nodes;
    std::vector<Edge> edges;
};
