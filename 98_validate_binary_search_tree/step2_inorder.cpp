#include <stack>
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

        std::stack<TreeNode*> nodes_to_visit;
        TreeNode* current_node = root;
        long long prev_value = LLONG_MIN;

        while (!nodes_to_visit.empty() || current_node) {
            while (current_node) {
                nodes_to_visit.emplace(current_node);
                current_node = current_node->left;
            }
            current_node = nodes_to_visit.top();
            nodes_to_visit.pop();

            if (prev_value >= current_node->val) {
                return false;
            }
            prev_value = current_node->val;
            current_node = current_node->right;
        }
        return true;
    }
};
