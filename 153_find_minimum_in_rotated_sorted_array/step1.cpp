#include <vector>
class Solution {
public:
    int findMin(std::vector<int>& nums) {
        if (nums.empty()) {
            return -1;
        }

        int begin = 0; 
        int end = nums.size();

        while (begin < end) {
            if (isIncreasingArray(nums, begin, end)) {
                return nums[begin];
            }

            int mid = begin + (end - begin) / 2;
            if (isIncreasingArray(nums, begin, mid)) {
                begin = mid;
            } else {
                end = mid;
            }
        }
        return nums[begin];
    }
private:
    bool isIncreasingArray(std::vector<int>& nums, int begin, int end) {
        int previous_num = nums[begin];
        for (int i = begin + 1; i < end; i++) {
            if (previous_num >= nums[i]) {
                return false;
            }
            previous_num = nums[i];
        }
        return true;
    }
};
