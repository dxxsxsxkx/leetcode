#include <vector>
class Solution {
public:
    int rob(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }

        int current_max_return = std::max(nums[0], nums[1]);

        int second_previous_max_return = nums[0];
        int previous_max_return = current_max_return;

        for (int i = 2; i < nums.size(); ++i) {
            current_max_return = std::max(previous_max_return, second_previous_max_return + nums[i]);
            
            second_previous_max_return = previous_max_return;
            previous_max_return = current_max_return;
        }

        return current_max_return;
    }
};
