#include <utility>
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
        // first element contains nodes with values smaller than v; 
        // second element contains nodes with values larger than v
        auto split = splitHelper(root, v);

        int left_count = countNode(split.first);
        int right_count = countNode(split.second);

        if (left_count > right_count) {
            return split.first;
        } else if (left_count < right_count) {
            return split.second;
        } else {
            if (!split.first) {
                return split.second;
            }
            if (!split.second) {
                return split.first;
            }
            return (split.first->val > split.second->val) ? 
                split.first : 
                split.second;
        }
    }
private:
    std::pair<TreeNode*, TreeNode*> splitHelper(TreeNode* root, int target) {
        if (!root) {
            return {nullptr, nullptr};
        }

        if (root->val <= target) {
            auto right_split = splitHelper(root->right, target);
            root->right = right_split.first;
            return {root, right_split.second};
        } else {
            auto left_split = splitHelper(root->left, target);
            root->left = left_split.second;
            return {left_split.first, root};
        }
    }
    int countNode(TreeNode* root) {
        if (!root) {
            return 0;
        }
        return 1 + countNode(root->left) + countNode(root->right);
    }
};
