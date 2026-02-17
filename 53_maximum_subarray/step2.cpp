#include <limits>
#include <vector>
class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        int current = nums[0];
        int best = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            current = std::max(current + nums[i], nums[i]);
            best = std::max(best, current);
        }

        return best;
    }
};
