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
    bool isValidBST(TreeNode* root) {
        if (!root) {
            return true;
        }

        std::queue<NodeAndRange> nodes_to_visit;
        nodes_to_visit.emplace(root, LLONG_MIN, LLONG_MAX);

        while (!nodes_to_visit.empty()) {
            const auto [node, min_val, max_val] = nodes_to_visit.front();
            nodes_to_visit.pop();

            if (node->val <= min_val || node->val >= max_val) {
                return false;
            }

            if (node->left) {
                nodes_to_visit.emplace(node->left, min_val, node->val);
            }
            if (node->right) {
                nodes_to_visit.emplace(node->right, node->val, max_val);
            }
        }

        return true;
    }
private:
    struct NodeAndRange {
        TreeNode* node;
        long long min_val;
        long long max_val;
    };
};
