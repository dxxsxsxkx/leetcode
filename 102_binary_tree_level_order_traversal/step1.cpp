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
        std::vector<std::vector<int>> nodes_by_level;

        if (!root) {
            return nodes_by_level;
        }

        std::queue<NodeAndLevel> visiting;
        visiting.emplace(root, 0);

        while (!visiting.empty()) {
            auto [node, level] = visiting.front();
            visiting.pop();

            if (nodes_by_level.size() == level) {
                nodes_by_level.emplace_back();
            }
            nodes_by_level[level].emplace_back(node->val);

            if (node->left) {
                visiting.emplace(node->left, level + 1);
            }
            if (node->right) {
                visiting.emplace(node->right, level + 1);
            }
        }

        return nodes_by_level;
    }
private:
    struct NodeAndLevel {
        TreeNode* node;
        int level;
    };
};
