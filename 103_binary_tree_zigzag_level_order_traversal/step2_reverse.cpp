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
        std::vector<TreeNode*> current_level_nodes = {root};
        bool from_right = false;

        while (!current_level_nodes.empty()) {
            std::vector<int> current_level_values;
            std::vector<TreeNode*> next_level_nodes;

            current_level_values.reserve(current_level_nodes.size());
            next_level_nodes.reserve(next_level_nodes.size() * 2);  // left and right

            for (TreeNode* node : current_level_nodes) {
                current_level_values.push_back(node->val);

                if (node->left) {
                    next_level_nodes.push_back(node->left);
                }
                if (node->right) {
                    next_level_nodes.push_back(node->right);
                }
            }

            if (from_right) {
                std::reverse(current_level_values.begin(), current_level_values.end());
            }

            level_sorted_values.push_back(std::move(current_level_values));
            current_level_nodes = std::move(next_level_nodes);
            from_right = !from_right;
        }

        return level_sorted_values;
    }
};
