#include <set>
#include <stack>
#include <vector>

class Solution {
public:
    int countComponents(int n, std::vector<std::vector<int>>& edges) {
        std::set<int> checked_nodes;

        std::vector<std::vector<int>> adjacency_list(n);
        for (auto& edge : edges) {
            adjacency_list[edge[0]].push_back(edge[1]);
            adjacency_list[edge[1]].push_back(edge[0]);
        }

        int n_components;

        for (int i = 0; i < n; ++i) {
            if (!checked_nodes.contains(i)) {
                checkAdjacentNode(i, checked_nodes, adjacency_list);
                ++n_components;
            }
        }

        return n_components;
    }

private:
    void checkAdjacentNode(
        int node_start,
        std::set<int>& checked_nodes,
        std::vector<std::vector<int>>& adjacency_list
    ) {
        std::stack<int> frontier;
        frontier.emplace(node_start);
        checked_nodes.emplace(node_start);

        while (!frontier.empty()) {
            int node_now = frontier.top();
            frontier.pop();
            for (auto& adjacent_node : adjacency_list[node_now]) {
                if (!checked_nodes.contains(adjacent_node)) {
                    checked_nodes.emplace(adjacent_node);
                    frontier.emplace(adjacent_node);
                }
            }
        }
    }
};
