#include <vector>
class Solution {
public:
    int findMin(std::vector<int>& nums) {
        if (nums.empty()) {
            throw std::invalid_argument("`nums` cannot be empty");
        }

        int begin = 0; 
        int end = nums.size();
        int last = nums.back();

        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            
            if (nums[mid] > last) {
                begin = mid + 1;
            } else {
                end = mid;
            }
        }
        return nums[begin];
    }
};
