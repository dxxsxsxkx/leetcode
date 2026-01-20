#include <algorithm>
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
    
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int left_depth = minDepth(root->left);
        int right_depth = minDepth(root->right);

        if (root->left && !root->right) {
            return left_depth + 1;
        }
        if (!root->left && root->right) {
            return right_depth + 1;
        }

        return std::min(left_depth, right_depth) + 1;
    }
};
