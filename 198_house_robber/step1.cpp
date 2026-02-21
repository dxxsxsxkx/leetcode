#include <vector>
class Solution {
public:
    int rob(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        // Maximum amount of money if you rob each house
        std::vector<int> max_returns(nums.size());
        max_returns[0] = nums[0];
        max_returns[1] = nums[1];

        for (int i = 2; i < nums.size(); ++i) {
            int total_return = 0;
            for (int j = 0; j < i - 1; ++j) {
                if (total_return < max_returns[j]) {
                    total_return = max_returns[j];
                }
            }
            max_returns[i] = total_return + nums[i];
        }
        
        return std::max(max_returns[nums.size() - 2], max_returns[nums.size() - 1]);
    }
};
