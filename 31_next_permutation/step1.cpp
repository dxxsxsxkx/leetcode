#include <algorithm>
#include <vector>
class Solution {
public:
    void nextPermutation(std::vector<int>& nums) {
        int i = nums.size() - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            --i;
        }
        
        // if i = -1, nums are already in the descending order
        // so simply using reverse is fine
        if (i >= 0) {
            int j = nums.size() - 1;
            while (nums[i] >= nums[j]) {
                --j;
            }
            std::swap(nums[i], nums[j]);
        }

        std::reverse(nums.begin() + i + 1, nums.end());
    }
};
