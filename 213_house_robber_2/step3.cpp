#include <algorithm>
#include <vector>
class Solution {
public:
    int rob(std::vector<int>& nums) {
        int num_houses = nums.size();

        if (num_houses == 1) {
            return nums[0];
        }

        return std::max(rangeRob(nums, 0, num_houses - 2), rangeRob(nums, 1, num_houses - 1));
    }
private:
    int rangeRob(const std::vector<int>& nums, int start, int end) {
        int current_max_return = 0;
        int previous_max_return = 0;
        int second_previous_max_return = 0;

        for (int i = start; i <= end; ++i) {
            current_max_return = std::max(second_previous_max_return + nums[i], previous_max_return);

            second_previous_max_return = previous_max_return;
            previous_max_return = current_max_return;
        }

        return current_max_return;
    }
};
