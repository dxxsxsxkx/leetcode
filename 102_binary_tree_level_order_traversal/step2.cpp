#include <queue>
#include <vector>
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
    std::vector<std::vector<int>> levelOrder(TreeNode* root) {
        std::vector<std::vector<int>> level_ordered_nodes;

        if (!root) {
            return level_ordered_nodes;
        }

        std::queue<NodeAndLevel> visiting;
        visiting.emplace(root, 0);

        while (!visiting.empty()) {
            auto [node, level] = visiting.front();
            visiting.pop();

            if (level_ordered_nodes.size() == level) {
                level_ordered_nodes.emplace_back();
            }
            level_ordered_nodes[level].emplace_back(node->val);

            if (node->left) {
                visiting.emplace(node->left, level + 1);
            }
            if (node->right) {
                visiting.emplace(node->right, level + 1);
            }
        }

        return level_ordered_nodes;
    }
private:
    struct NodeAndLevel {
        TreeNode* node;
        int level;
    };
};
