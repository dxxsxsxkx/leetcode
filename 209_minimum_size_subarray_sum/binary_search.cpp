#include <algorithm>
#include <limits>
#include <vector>
class Solution {
public:
    int minSubArrayLen(int target, std::vector<int>& nums) {
        std::vector<int> prefix_sum(nums.size() + 1);
        for (int i = 0; i < nums.size(); ++i) {
            prefix_sum[i + 1] = prefix_sum[i] + nums[i];
        }

        int min_size = std::numeric_limits<int>::max();

        for (int right = 0; right < nums.size(); ++right) {
            int remaining = prefix_sum[right + 1] - target;

            // Largest `left` where prefix_sum[left] <= remaining            
            auto it = std::upper_bound(prefix_sum.begin(), prefix_sum.end(), remaining);

            if (it != prefix_sum.begin()) {
                int left = (it - prefix_sum.begin()) - 1;
                min_size = std::min(min_size, right - left + 1);
            }
        }

        return (min_size == std::numeric_limits<int>::max()) ? 0 : min_size;
    }
};
