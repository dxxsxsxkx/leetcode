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
        TreeNode* node_new;
    };
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (!root1) {
            return root2;
        }
        if (!root2) {
            return root1;
        }

        int sum_two_nodes = root1->val + root2->val;
        TreeNode* root_new = new TreeNode(sum_two_nodes);

        std::queue<ThreeNodes> visiting;
        visiting.emplace(root1, root2, root_new);

        while (!visiting.empty()) {
            auto [node1, node2, node_new] = visiting.front();
            visiting.pop();

            // lhs node
            TreeNode* left1 = node1 ? node1->left : nullptr;
            TreeNode* left2 = node2 ? node2->left : nullptr;
            
            if (left1 && left2) {
                node_new->left = new TreeNode(left1->val + left2->val);
                visiting.emplace(left1, left2, node_new->left);
            }
            if (left1 && !left2) {
                node_new->left = new TreeNode(left1->val);
                visiting.emplace(left1, nullptr, node_new->left);
            }
            if (!left1 && left2) {
                node_new->left = new TreeNode(left2->val);
                visiting.emplace(nullptr, left2, node_new->left);
            }

            // rhs node
            TreeNode* right1 = node1 ? node1->right : nullptr;
            TreeNode* right2 = node2 ? node2->right : nullptr;

            if (right1 && right2) {
                node_new->right = new TreeNode(right1->val + right2->val);
                visiting.emplace(right1, right2, node_new->right);
            }
            if (right1 && !right2) {
                node_new->right = new TreeNode(right1->val);
                visiting.emplace(right1, nullptr, node_new->right);
            }
            if (!right1 && right2) {
                node_new->right = new TreeNode(right2->val);
                visiting.emplace(nullptr, right2, node_new->right);
            }
        }

        return root_new;
    }
};
