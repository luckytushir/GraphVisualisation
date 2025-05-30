#include <iostream>
#include "Algorithms.h"
#include "Visualization.h"
#include <queue>
#include <chrono>
#include <stack>
#include <functional>

namespace Algorithms {

    // Global state for animated algorithms
    static std::queue<int> bfsQueue;
    static std::stack<int> dfsStack;
    static std::vector<bool> visited;
    static bool algorithmRunning = false;
    static bool isBFS = false;
    static auto lastUpdateTime = std::chrono::steady_clock::now();
    static Graph* currentGraph = nullptr;
    static Visualization* currentViz = nullptr;

    void startBFS(Graph& graph, Visualization& visualization, int startNode) {
        // Initialize BFS
        currentGraph = &graph;
        currentViz = &visualization;
        int n = graph.getNodeCount();
        visited.assign(n, false);

        // Clear queue and setup
        while (!bfsQueue.empty()) bfsQueue.pop();

        bfsQueue.push(startNode);
        visited[startNode] = true;
        visualization.clearVisited();
        visualization.setVisited(startNode);

        algorithmRunning = true;
        isBFS = true;
        lastUpdateTime = std::chrono::steady_clock::now();
    }

    void startDFS(Graph& graph, Visualization& visualization, int startNode) {
        // Initialize DFS
        currentGraph = &graph;
        currentViz = &visualization;
        int n = graph.getNodeCount();
        visited.assign(n, false);

        // Clear stack and setup
        while (!dfsStack.empty()) dfsStack.pop();

        dfsStack.push(startNode);
        visualization.clearVisited();

        algorithmRunning = true;
        isBFS = false;
        lastUpdateTime = std::chrono::steady_clock::now();
    }

    void updateAnimation() {
        if (!algorithmRunning || !currentGraph || !currentViz) return;

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdateTime);

        // Update every 800ms for better visibility
        if (elapsed.count() < 800) return;

        lastUpdateTime = now;

        if (isBFS) {
            // Continue BFS animation
            if (bfsQueue.empty()) {
                algorithmRunning = false;
                return;
            }

            int current = bfsQueue.front();
            bfsQueue.pop();

            // Add ALL unvisited neighbors to queue (not just one)
            bool foundNeighbor = false;
            for (const auto& edge : currentGraph->getEdges()) {
                if (edge.from == current && !visited[edge.to]) {
                    visited[edge.to] = true;
                    bfsQueue.push(edge.to);
                    currentViz->setVisited(edge.to);
                    foundNeighbor = true;
                    // Don't break here - process all neighbors
                }
            }

            // If we found neighbors, only show one per frame for animation
            // but make sure to process all of them in the queue
            if (foundNeighbor) {
                // Continue processing if there are more nodes in queue
                return;
            }
        }
        else {
            // Continue DFS animation
            if (dfsStack.empty()) {
                algorithmRunning = false;
                return;
            }

            int current = dfsStack.top();
            dfsStack.pop();

            if (!visited[current]) {
                visited[current] = true;
                currentViz->setVisited(current);

                // Add ALL unvisited neighbors to stack (in reverse order for proper DFS)
                std::vector<int> neighbors;
                for (const auto& edge : currentGraph->getEdges()) {
                    if (edge.from == current && !visited[edge.to]) {
                        neighbors.push_back(edge.to);
                    }
                }

                // Add neighbors to stack in reverse order for proper DFS traversal
                for (int i = neighbors.size() - 1; i >= 0; i--) {
                    dfsStack.push(neighbors[i]);
                }
            }
        }
    }

    bool isAnimating() {
        return algorithmRunning;
    }

    // Complete traversal functions (non-animated versions)
    void completeBFS(Graph& graph, Visualization& visualization, int startNode) {
        int n = graph.getNodeCount();
        std::vector<bool> localVisited(n, false);
        std::queue<int> queue;

        visualization.clearVisited();

        // Handle disconnected components
        for (int start = 0; start < n; start++) {
            if (!localVisited[start]) {
                queue.push(start);
                localVisited[start] = true;
                visualization.setVisited(start);

                while (!queue.empty()) {
                    int current = queue.front();
                    queue.pop();

                    // Add all unvisited neighbors
                    for (const auto& edge : graph.getEdges()) {
                        if (edge.from == current && !localVisited[edge.to]) {
                            localVisited[edge.to] = true;
                            queue.push(edge.to);
                            visualization.setVisited(edge.to);
                        }
                    }
                }
            }
        }
    }

    void completeDFS(Graph& graph, Visualization& visualization, int startNode) {
        int n = graph.getNodeCount();
        std::vector<bool> localVisited(n, false);

        visualization.clearVisited();

        // Recursive helper function
        std::function<void(int)> dfsHelper = [&](int node) {
            localVisited[node] = true;
            visualization.setVisited(node);

            for (const auto& edge : graph.getEdges()) {
                if (edge.from == node && !localVisited[edge.to]) {
                    dfsHelper(edge.to);
                }
            }
            };

        // Handle disconnected components
        for (int start = 0; start < n; start++) {
            if (!localVisited[start]) {
                dfsHelper(start);
            }
        }
    }

    // Legacy functions for compatibility
    void BFS(Graph& graph, Visualization& visualization, int startNode) {
        startBFS(graph, visualization, startNode);
    }

    void DFS(Graph& graph, Visualization& visualization, int startNode) {
        startDFS(graph, visualization, startNode);
    }
}