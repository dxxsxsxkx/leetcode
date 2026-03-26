#include <vector>
class Solution {
public:
    void moveZeroes(std::vector<int>& nums) {
        int num_zeros = 0;

        for (int i = 0; i < nums.size(); ) {
            if (nums[i] == 0) {
                ++num_zeros;
                nums.erase(nums.begin() + i);
            } else {
                ++i;
            }
        }

        while (num_zeros > 0) {
            nums.push_back(0);
            --num_zeros;
        }
    }
};
