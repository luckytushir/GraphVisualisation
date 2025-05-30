#pragma once

#include "Graph.h"
#include "Visualization.h"

namespace Algorithms {
    // Main algorithm functions (animated)
    void BFS(Graph& graph, Visualization& visualization, int startNode);
    void DFS(Graph& graph, Visualization& visualization, int startNode);

    // Animation control functions
    void startBFS(Graph& graph, Visualization& visualization, int startNode);
    void startDFS(Graph& graph, Visualization& visualization, int startNode);
    void updateAnimation();
    bool isAnimating();

    // Complete traversal functions (non-animated, handles disconnected components)
    void completeBFS(Graph& graph, Visualization& visualization, int startNode);
    void completeDFS(Graph& graph, Visualization& visualization, int startNode);
}