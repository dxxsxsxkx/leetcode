#include <vector>
class Solution {
public:
    int searchInsert(std::vector<int>& nums, int target) {
        return binarySearch(nums, 0, nums.size(), target);
    }
private:
    int binarySearch(const std::vector<int>& nums, int begin, int end, const int target) {
        if (begin >= end) {
            return begin;
        }

        int mid = begin + (end - begin) / 2;

        if (target <= nums[mid]) {
            return binarySearch(nums, begin, mid, target);
        } else {
            return binarySearch(nums, mid + 1, end, target);
        }
    }
};
