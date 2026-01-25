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
        return explorePath(root, 0, targetSum);
    }
private:
    bool explorePath(TreeNode* node, int current_sum, int target_sum) {
        if (!node) {
            return false;
        }

        int new_sum = current_sum + node->val;

        if (!node->left && !node->right) {
            if (new_sum == target_sum) {
                return true;
            }
        }

        bool left = explorePath(node->left, new_sum, target_sum);
        bool right = explorePath(node->right, new_sum, target_sum);
        return left || right;
    }
};
