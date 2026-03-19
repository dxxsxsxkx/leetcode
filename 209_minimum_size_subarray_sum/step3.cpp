#include <limits>
#include <vector>
class Solution {
public:
    int minSubArrayLen(int target, std::vector<int>& nums) {
        int left = 0;
        int min_size = std::numeric_limits<int>::max();
        int subarray_sum = 0;

        for (int right = 0; right < nums.size(); ++right) {
            subarray_sum += nums[right];

            while (subarray_sum >= target) {
                min_size = std::min(min_size, right - left + 1);
                subarray_sum -= nums[left];
                ++left;
            }
        }

        return (min_size == std::numeric_limits<int>::max()) ? 0 : min_size;
    }
};
