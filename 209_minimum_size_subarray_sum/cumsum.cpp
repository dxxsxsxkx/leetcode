#include <limits>
#include <vector>
class Solution {
public:
    int minSubArrayLen(int target, std::vector<int>& nums) {
        std::vector<int> cumulative_sum(nums.size() + 1);
        cumulative_sum[0] = 0;
        for (int i = 0; i < nums.size(); ++i) {
            cumulative_sum[i + 1] = cumulative_sum[i] + nums[i];
        }

        int min_size = std::numeric_limits<int>::max();
        int left = 0;
        int right = 1;

        while (right < cumulative_sum.size()) {
            while (left < right) {
                if (cumulative_sum[right] - cumulative_sum[left] < target) {
                    break;
                }
                min_size = std::min(min_size, right - left);
                ++left;
            }
            ++right;
        }

        return (min_size == std::numeric_limits<int>::max()) ? 0 : min_size;
    }
};
