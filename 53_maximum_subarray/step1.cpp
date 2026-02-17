#include <limits>
#include <vector>
class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        int cumsum = 0;
        int min_cumsum = 0;
        int max_sum = nums[0];

        for (auto num : nums) {
            cumsum += num;
            max_sum = std::max(max_sum, cumsum - min_cumsum);
            min_cumsum = std::min(min_cumsum, cumsum);
        }

        return max_sum;
    }
};
