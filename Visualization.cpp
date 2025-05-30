#include "Visualization.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

Visualization::Visualization(Graph& graph)
    : graph(graph)
    , nodeShape(10.f)
{
    nodeShape.setFillColor(sf::Color::Green);

    static sf::Font staticFont;
    if (!staticFont.openFromFile("assets/font/NotoSerifTodhri-Regular.ttf")) {
        std::cerr << "Error loading font!\n";
    }
    font = staticFont;

    // Don't initialize visited vector here - it will be done dynamically
}

void Visualization::setVisited(int nodeIndex) {
    // Ensure visited vector is large enough
    if (visited.size() < static_cast<size_t>(graph.getNodeCount())) {
        visited.resize(graph.getNodeCount(), false);
    }

    if (nodeIndex >= 0 && nodeIndex < static_cast<int>(visited.size()))
        visited[nodeIndex] = true;
}

void Visualization::clearVisited() {
    // Ensure visited vector matches current node count
    visited.resize(graph.getNodeCount(), false);
    std::fill(visited.begin(), visited.end(), false);
}

void Visualization::updateNodeCount() {
    // Resize visited vector to match current node count
    visited.resize(graph.getNodeCount(), false);
}

void Visualization::draw(sf::RenderWindow& window) {
    const auto& nodes = graph.getNodes();
    const auto& edges = graph.getEdges();

    // Ensure visited vector is properly sized
    if (visited.size() != nodes.size()) {
        visited.resize(nodes.size(), false);
    }

    // Draw edges with proper color and thickness
    for (const auto& edge : edges) {
        if (edge.from < static_cast<int>(nodes.size()) && edge.to < static_cast<int>(nodes.size())) {
            sf::Vector2f a(nodes[edge.from].position);
            sf::Vector2f b(nodes[edge.to].position);
            sf::Vertex line[] = {
                sf::Vertex(a, sf::Color::Black),
                sf::Vertex(b, sf::Color::Black)
            };
            window.draw(line, 2, sf::PrimitiveType::Lines);
        }
    }

    // Draw nodes and labels
    for (int i = 0; i < static_cast<int>(nodes.size()); ++i) {
        sf::Vector2f pos(nodes[i].position);
        nodeShape.setPosition(pos - sf::Vector2f(nodeShape.getRadius(), nodeShape.getRadius()));

        // Safe access to visited array
        bool isVisited = (i < static_cast<int>(visited.size())) ? visited[i] : false;
        nodeShape.setFillColor(isVisited ? sf::Color::Yellow : sf::Color::Green);
        window.draw(nodeShape);

        // Create and configure the text label
        sf::Text label(font);
        label.setString(std::to_string(nodes[i].data));
        label.setCharacterSize(14);
        label.setFillColor(sf::Color::Black);

        // Simple approach: position text slightly offset from node center
        // This avoids the bounds calculation issues
        float nodeCenterX = pos.x;
        float nodeCenterY = pos.y;

        // Offset text by a small amount to center it roughly on the node
        float textX = nodeCenterX - 8.0f;  // Approximate offset for centering
        float textY = nodeCenterY - 8.0f;  // Approximate offset for centering

        // Set the text position and draw
        label.setPosition(sf::Vector2f(textX, textY));
        window.draw(label);
    }
}