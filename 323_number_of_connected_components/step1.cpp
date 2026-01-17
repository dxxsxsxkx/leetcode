#include <set>
#include <stack>
#include <vector>

class Solution {
public:
    int n;
    std::vector<std::vector<int>>* edges;
    std::set<int> checked_nodes;

    int countComponents(int n_, std::vector<std::vector<int>>& edges_) {
        n = n_;
        edges = &edges_;
        
        int n_components = 0;
        for (int i = 0; i < n; ++i) {
            if (!checked_nodes.contains(i)) {
                exploreNode(i);
                ++n_components;
            }
        }
        return n_components;
    };

    bool isConnected(int node_a, int node_b) {
        for (auto& e : *edges) {
            if (e[0] == node_a && e[1] == node_b) {
                return true;
            }
            if (e[0] == node_b && e[1] == node_a) {
                return true;
            }
        }
        return false;
    }

    void exploreNode(int node_start) {
        std::stack<int> frontier;
        frontier.emplace(node_start);
        checked_nodes.emplace(node_start);
        
        while (!frontier.empty()) {
            int node_now = frontier.top();
            frontier.pop();
            for (int j = 0; j < n; ++j) {
                if (!checked_nodes.contains(j) && isConnected(node_now, j)) {
                    checked_nodes.emplace(j);
                    frontier.emplace(j);
                }
            }
        }
    }
};
