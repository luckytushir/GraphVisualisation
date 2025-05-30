#pragma once

#include <SFML/Graphics.hpp>
#include "Graph.h"
#include <vector>

class Visualization {
public:
    Visualization(Graph& graph);
    void draw(sf::RenderWindow& window);
    void setVisited(int nodeIndex);
    void clearVisited();
    void updateNodeCount(); // Add this method

private:
    Graph& graph;
    sf::CircleShape nodeShape;
    sf::Font font;
    std::vector<bool> visited;
};