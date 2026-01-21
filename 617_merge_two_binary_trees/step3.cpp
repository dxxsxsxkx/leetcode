#include <queue>
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
    struct ThreeNodes {
        TreeNode* node1;
        TreeNode* node2;
        TreeNode* new_node;
    };
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (!root1 && !root2) {
            return nullptr;
        }
        if (!root1) {
            return root2;
        }
        if (!root2) {
            return root1;
        }

        TreeNode* new_root = new TreeNode(root1->val + root2->val);

        std::queue<ThreeNodes> visiting;
        visiting.emplace(root1, root2, new_root);

        while (!visiting.empty()) {
            auto [node1, node2, new_node] = visiting.front();
            visiting.pop();

            TreeNode* left1 = node1 ? node1->left : nullptr;
            TreeNode* left2 = node2 ? node2->left : nullptr;

            if (left1 || left2) {
                int new_left_val = (left1 ? left1->val : 0) + (left2 ? left2->val : 0);
                new_node->left = new TreeNode(new_left_val);
                visiting.emplace(left1, left2, new_node->left);
            }

            TreeNode* right1 = node1 ? node1->right : nullptr;
            TreeNode* right2 = node2 ? node2->right : nullptr;

            if (right1 || right2) {
                int new_right_val = (right1 ? right1->val : 0) + (right2 ? right2->val : 0);
                new_node->right = new TreeNode(new_right_val);
                visiting.emplace(right1, right2, new_node->right);
            }
        }
        return new_root;
    }
};
