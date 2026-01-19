#include <algorithm>
#include <queue>
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

    struct NodeAndDepth {
        TreeNode* node;
        int depth;
    };

    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        std::queue<NodeAndDepth> next_node;
        next_node.emplace(root, 1);

        int max_depth = 0;
        while (!next_node.empty()) {
            auto [current_node, current_depth] = next_node.front();
            next_node.pop();

            max_depth = std::max(max_depth, current_depth);

            if (current_node->left) {
                next_node.emplace(current_node->left, current_depth + 1);
            }
            if (current_node->right) {
                next_node.emplace(current_node->right, current_depth + 1);
            }
        }
        return max_depth;
    }
};
