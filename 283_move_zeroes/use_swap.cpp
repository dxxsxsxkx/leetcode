#include <algorithm>
#include <vector>
class Solution {
public:
    void moveZeroes(std::vector<int>& nums) {
        int insert_pos = 0;

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                std::swap(nums[insert_pos], nums[i]);
                ++insert_pos;
            }
        }
    }
};
