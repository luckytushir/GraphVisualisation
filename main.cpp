#include <SFML/Graphics.hpp>
#include "Graph.h"
#include <iostream>
#include "Visualization.h"
#include "Algorithms.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Window/VideoMode.hpp>  
#include <SFML/Window.hpp>

using namespace sf;

int main() {
    Vector2u windowSize{ 1280, 720 };
    RenderWindow window(VideoMode(windowSize), "Graph Visualization");
    window.setFramerateLimit(60);

    // Initialize ImGui
    if (!ImGui::SFML::Init(window)) {
        std::cerr << "Failed to initialize ImGui-SFML!" << std::endl;
        return -1;
    }

    Graph graph;
    Visualization visualization(graph);

    // UI state variables
    static int startNode = 0;
    int sourceNode = 0, targetNode = 0;
    bool directed = false;
    static int nodeData = 0, nodeX = 100, nodeY = 100;

    Clock deltaClock;
    bool running = true;

    while (running) {
        // Handle events
        while (auto evt = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *evt);
            if (evt->is<Event::Closed>())
                running = false;
        }

        // Update ImGui
        ImGui::SFML::Update(window, deltaClock.restart());

        // Update algorithm animation
        Algorithms::updateAnimation();

        // Create ImGui windows
        ImGui::Begin("Graph Controls");

        // Node creation section
        ImGui::Text("Add Nodes");
        ImGui::InputInt("Node Data", &nodeData);
        ImGui::InputInt("Node X", &nodeX);
        ImGui::InputInt("Node Y", &nodeY);
        if (ImGui::Button("Add Node")) {
            graph.addNode(Vector2u(nodeX, nodeY), nodeData);
            // Update visualization to handle new node count
            visualization.updateNodeCount();
        }

        ImGui::Separator();

        // Edge creation section
        ImGui::Text("Add Edges");
        ImGui::InputInt("Source Node", &sourceNode);
        ImGui::InputInt("Target Node", &targetNode);
        ImGui::Checkbox("Directed?", &directed);
        if (ImGui::Button("Add Edge")) {
            graph.addEdge(sourceNode, targetNode, directed);
        }

        ImGui::Separator();

        // Graph info
        ImGui::Text("Graph Info");
        ImGui::Text("Nodes: %d", graph.getNodeCount());
        ImGui::Text("Edges: %d", graph.getEdgeCount());

        ImGui::Separator();

        // Algorithm section
        ImGui::Text("Algorithms (Animated)");
        ImGui::InputInt("Start Node", &startNode);

        if (ImGui::Button("Run Animated BFS")) {
            if (startNode >= 0 && startNode < graph.getNodeCount() && !Algorithms::isAnimating()) {
                Algorithms::BFS(graph, visualization, startNode);
            }
            else if (Algorithms::isAnimating()) {
                std::cout << "Animation already running! Please wait..." << std::endl;
            }
            else {
                std::cout << "Invalid start node! Must be between 0 and " << (graph.getNodeCount() - 1) << std::endl;
            }
        }

        if (ImGui::Button("Run Animated DFS")) {
            if (startNode >= 0 && startNode < graph.getNodeCount() && !Algorithms::isAnimating()) {
                Algorithms::DFS(graph, visualization, startNode);
            }
            else if (Algorithms::isAnimating()) {
                std::cout << "Animation already running! Please wait..." << std::endl;
            }
            else {
                std::cout << "Invalid start node! Must be between 0 and " << (graph.getNodeCount() - 1) << std::endl;
            }
        }

        ImGui::Separator();

        // Complete traversal section
        ImGui::Text("Complete Traversals (All Nodes)");

        if (ImGui::Button("Complete BFS (All Components)")) {
            if (graph.getNodeCount() > 0 && !Algorithms::isAnimating()) {
                Algorithms::completeBFS(graph, visualization, 0);
                std::cout << "Complete BFS finished - all reachable nodes visited!" << std::endl;
            }
            else if (Algorithms::isAnimating()) {
                std::cout << "Animation already running! Please wait..." << std::endl;
            }
        }

        if (ImGui::Button("Complete DFS (All Components)")) {
            if (graph.getNodeCount() > 0 && !Algorithms::isAnimating()) {
                Algorithms::completeDFS(graph, visualization, 0);
                std::cout << "Complete DFS finished - all reachable nodes visited!" << std::endl;
            }
            else if (Algorithms::isAnimating()) {
                std::cout << "Animation already running! Please wait..." << std::endl;
            }
        }

        ImGui::Separator();

        // Clear and reset section
        if (ImGui::Button("Clear Graph")) {
            graph.clear();
            visualization.clearVisited();
        }

        if (ImGui::Button("Clear Visited")) {
            visualization.clearVisited();
        }

        ImGui::End();

        // Render everything
        window.clear(Color::White);
        visualization.draw(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}