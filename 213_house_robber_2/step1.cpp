#include <algorithm>
#include <vector>
class Solution {
public:
    int rob(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        std::vector<std::vector<int>> max_returns(nums.size(), std::vector<int>(2, 0));

        // Did not rob nums[0]
        max_returns[0][0] = 0;
        max_returns[1][0] = nums[1];

        // Robbed nums[0]
        max_returns[0][1] = nums[0];
        max_returns[1][1] = nums[0];

        for (int i = 2; i < nums.size(); ++i) {
            // Did not rob nums[0]
            max_returns[i][0] = std::max(max_returns[i - 2][0] + nums[i], max_returns[i - 1][0]);

            // Robbed nums[0]
            if (i == nums.size() - 1) {
                max_returns[i][1] = max_returns[i - 1][1];
            } else {
                max_returns[i][1] = std::max(max_returns[i - 2][1] + nums[i], max_returns[i - 1][1]);
            }
        }

        return std::max(max_returns.back()[0], max_returns.back()[1]);
    }
};
