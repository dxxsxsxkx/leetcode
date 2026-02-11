#include <unordered_map>
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
    std::unordered_map<int, int> inorder_to_preorder;
    int preorder_idx = 0;

    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
        if (preorder.empty()) {
            return nullptr;
        }

        for (int i = 0; i < preorder.size(); ++i) {
            inorder_to_preorder[inorder[i]] = i;
        }

        return helper(preorder, 0, inorder.size() - 1);
    }
private: 
    TreeNode* helper(std::vector<int>& preorder, int leftmost, int rightmost) {
        if (leftmost > rightmost) {
            return nullptr;
        }

        int root_val = preorder[preorder_idx++]; 
        TreeNode* root = new TreeNode(root_val);

        int index = inorder_to_preorder[root_val];

        root->left = helper(preorder, leftmost, index - 1);
        root->right = helper(preorder, index + 1, rightmost);

        return root;
    }
};
