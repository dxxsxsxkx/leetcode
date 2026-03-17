/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param root: the given tree
     * @param v: the target value
     * @return: the root TreeNode after splitting
     */
    TreeNode* splitBST(TreeNode *root, int v) {
        // left: smaller than / equal to v
        // right: larger than v
        TreeNode* left_root = nullptr;
        TreeNode* right_root = nullptr;
        TreeNode** left_subtree_next = &left_root;
        TreeNode** right_subtree_next = &right_root;

        TreeNode* node = root;
        while (node) {
            if (node->val <= v) {
                *left_subtree_next = node;
                TreeNode* tmp = node->right;
                node->right = nullptr;
                left_subtree_next = &node->right;
                node = tmp;
            } else {
                *right_subtree_next = node;
                TreeNode* tmp = node->left;
                node->left = nullptr;
                right_subtree_next = &node->left;
                node = tmp;
            }
        }
        
        int left_count = countNode(left_root);
        int right_count = countNode(right_root);

        if (left_count > right_count) {
            return left_root;
        } else if (left_count < right_count){
            return right_root;
        }

        return (left_root->val > right_root->val) ? left_root : right_root;
    }
private:
    int countNode(TreeNode* root) {
        if (!root) {
            return 0;
        }
        return 1 + countNode(root->left) + countNode(root->right);
    }
};
