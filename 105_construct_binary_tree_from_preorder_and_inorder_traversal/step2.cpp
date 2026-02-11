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
    int preorder_index = 0;
    TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
        if (inorder.empty()) {
            return nullptr;
        }

        int root_val = preorder[preorder_index++];
        TreeNode* node = new TreeNode(root_val);

        auto position = std::find(inorder.begin(), inorder.end(), root_val);
        std::vector<int> left_inorder(inorder.begin(), position);
        std::vector<int> right_inorder(position + 1, inorder.end());

        node->left = buildTree(preorder, left_inorder);
        node->right = buildTree(preorder, right_inorder);

        return node;
    }
};
