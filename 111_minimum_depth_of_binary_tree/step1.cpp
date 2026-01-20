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
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        std::queue<NodeAndDepth> visiting;
        visiting.emplace(root, 1);

        while (!visiting.empty()) {
            auto [node, level] = visiting.front();
            visiting.pop();
            
            if (!node->left && !node->right) {
                return level;
            }

            if (node->left) {
                visiting.emplace(node->left, level + 1);
            }
            if (node->right) {
                visiting.emplace(node->right, level + 1);
            }
        }

        return 0;
    }
};
