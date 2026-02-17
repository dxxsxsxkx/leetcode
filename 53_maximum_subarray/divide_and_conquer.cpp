#include <limits>
#include <vector>
class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        return helper(nums, 0, nums.size() - 1);
    }
private: 
    int helper(std::vector<int>& nums, int left, int right) {
        if (left == right) {
            return nums[left];
        }

        int mid = left + (right - left) / 2;
        
        int max_left = helper(nums, left, mid);
        int max_right = helper(nums, mid + 1, right);

        // cross
        int sum_left = std::numeric_limits<int>::min();
        int sum = 0;
        for (int i = mid; i >= left; i--) {
            sum += nums[i];
            sum_left = std::max(sum_left, sum);
        }

        int sum_right = std::numeric_limits<int>::min();
        sum = 0;
        for (int i = mid + 1; i <= right; i++) {
            sum += nums[i];
            sum_right = std::max(sum_right, sum);
        }

        int sum_cross = sum_left + sum_right;

        return std::max({max_left, max_right, sum_cross});
    }
};
