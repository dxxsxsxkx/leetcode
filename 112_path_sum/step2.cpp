#include <stack>
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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return false;
        }
        
        std::stack<NodeAndSum> visiting;
        visiting.emplace(root, root->val);

        while (!visiting.empty()) {
            auto [node, sum] = visiting.top();
            visiting.pop();

            if (!node->left && !node->right) {
                if (sum == targetSum) {
                    return true;
                }
            }

            if (node->left) {
                visiting.emplace(node->left, sum + node->left->val);
            }
            if (node->right) {
                visiting.emplace(node->right, sum + node->right->val);
            }
        }
        return false;
    }
private:
    struct NodeAndSum {
        TreeNode* node;
        int sum;
    };
};
