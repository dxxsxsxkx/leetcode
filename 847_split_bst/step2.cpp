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
        auto split_trees = splitHelper(root, v);
        
        int left_count = countNode(split_trees.first);
        int right_count = countNode(split_trees.second);

        if (left_count > right_count) {
            return split_trees.first;
        } else if (left_count < right_count) {
            return split_trees.second;
        } else {
            if (!split_trees.first) {
                return split_trees.second;
            }
            if (!split_trees.second) {
                return split_trees.first;
            }
            return (split_trees.first->val > split_trees.second->val) ? 
                split_trees.first : 
                split_trees.second;
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
