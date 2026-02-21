#include <vector>
class Solution {
public:
    int rob(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        std::vector<int> max_returns(nums.size());
        max_returns[0] = nums[0];
        max_returns[1] = std::max(nums[0], nums[1]);

        for (int i = 2; i < nums.size(); ++i) {
            max_returns[i] = std::max(max_returns[i - 1], max_returns[i - 2] + nums[i]);
        }

        return max_returns[nums.size() - 1];
    }
};
