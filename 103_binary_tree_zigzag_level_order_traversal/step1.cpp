#include<queue>
#include<vector>

class Solution {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
    std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root) {
            return {};
        }

        std::vector<std::vector<int>> level_sorted_values;
        std::queue<NodeAndLevel> nodes_to_visit;
        nodes_to_visit.emplace(root, 0);

        while (!nodes_to_visit.empty()) {
            auto [node, current_level] = nodes_to_visit.front();
            nodes_to_visit.pop();

            while (current_level >= level_sorted_values.size()) {
                level_sorted_values.emplace_back();
            }
            level_sorted_values[current_level].emplace_back(node->val);

            if (node->left) {
                nodes_to_visit.emplace(node->left, current_level + 1);
            }
            if (node->right) {
                nodes_to_visit.emplace(node->right, current_level + 1);
            }    
        }

        for (int i = 1; i < level_sorted_values.size(); i += 2) {
            std::reverse(level_sorted_values[i].begin(), level_sorted_values[i].end());
        }

        return level_sorted_values;
    }
private:
    struct NodeAndLevel {
        TreeNode* node;
        int level;
    };
};
