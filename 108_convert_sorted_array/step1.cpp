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

        return makeTree(nums, 0, nums.size());
    }
private:
    TreeNode* makeTree(std::vector<int>& nums, int idx_start, int idx_end) {
        if (idx_start == idx_end) {
            return nullptr;
        }

        int idx_middle = (idx_start + idx_end) / 2;
        TreeNode* root = new TreeNode(nums[idx_middle]);
        root->left = makeTree(nums, idx_start, idx_middle);
        root->right = makeTree(nums, idx_middle + 1, idx_end);
        return root;
    }
};
