#include <algorithm>
#include <vector>
class Solution {
public:
    void moveZeroes(std::vector<int>& nums) {
        auto pos_last_nonzero = std::remove(nums.begin(), nums.end(), 0);
        std::fill(pos_last_nonzero, nums.end(), 0);
    }
};
