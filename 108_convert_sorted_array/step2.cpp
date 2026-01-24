#include <queue>
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
    TreeNode* sortedArrayToBST(std::vector<int>& nums) {
        if (nums.empty()) {
            return nullptr;
        }

        TreeNode* new_root = new TreeNode();
        std::queue<NodeAndIndices> visiting;
        visiting.emplace(new_root, 0, nums.size() - 1);

        while (!visiting.empty()) {
            auto [node, idx_start, idx_end] = visiting.front();
            visiting.pop();

            int idx_middle = (idx_start + idx_end) / 2;
            node->val = nums[idx_middle];

            if (idx_start < idx_middle) {
                node->left = new TreeNode();
                visiting.emplace(node->left, idx_start, idx_middle - 1);
            }

            if (idx_middle < idx_end) {
                node->right = new TreeNode();
                visiting.emplace(node->right, idx_middle + 1, idx_end);
            }
        }
        return new_root;

    }
private:
    struct NodeAndIndices {
        TreeNode* node;
        int idx_start;
        int idx_end;
    };
};
