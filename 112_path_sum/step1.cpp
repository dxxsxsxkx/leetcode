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

        int remaining = targetSum - root->val;

        if (!root->left && !root->right) {
            if (remaining == 0) {
                return true;
            }
        }

        bool left = hasPathSum(root->left, remaining);
        bool right = hasPathSum(root->right, remaining);

        return left || right;
    }
};
