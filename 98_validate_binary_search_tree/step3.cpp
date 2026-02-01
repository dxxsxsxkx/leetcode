#include <climits>
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

        return helper(root, LLONG_MIN, LLONG_MAX);
    }
private:
    bool helper(TreeNode* node, long long min_value, long long max_value) {
        if (!node) {
            return true;
        }

        if (node->val <= min_value || node->val >= max_value) {
            return false;
        }

        bool left_is_valid = helper(node->left, min_value, node->val);
        bool right_is_valid = helper(node->right, node->val, max_value);

        return left_is_valid && right_is_valid;
    }
};
