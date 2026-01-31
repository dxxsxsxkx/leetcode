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
        std::queue<TreeNode*> nodes_to_visit;
        nodes_to_visit.emplace(root);
        bool from_right = false;

        while (!nodes_to_visit.empty()) {
            int n_current_level_nodes = nodes_to_visit.size();
            std::deque<int> current_level_values;

            for (int i = 0; i < n_current_level_nodes; ++i) {
                TreeNode* node = nodes_to_visit.front();
                nodes_to_visit.pop();

                if (from_right) {
                    current_level_values.push_front(node->val);
                } else {
                    current_level_values.push_back(node->val);
                }

                if (node->left) {
                    nodes_to_visit.emplace(node->left);
                }
                if (node->right) {
                    nodes_to_visit.emplace(node->right);
                }
            }

            level_sorted_values.emplace_back(current_level_values.begin(), current_level_values.end());
            from_right = !from_right;
        }

        return level_sorted_values;
    }
};
