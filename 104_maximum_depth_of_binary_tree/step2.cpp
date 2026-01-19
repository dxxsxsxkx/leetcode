# include <queue>
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

    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        std::queue<TreeNode*> next_nodes;
        next_nodes.emplace(root);

        int depth = 0;

        while (!next_nodes.empty()) {
            int n_next_nodes = next_nodes.size();
            ++depth;

            for (int i = 0; i < n_next_nodes; ++i) {
                TreeNode* current_node = next_nodes.front();
                next_nodes.pop();

                if (current_node->left) {
                    next_nodes.emplace(current_node->left);
                }
                if (current_node->right) {
                    next_nodes.emplace(current_node->right);
                }
            }
        }

        return depth;
    }
};
