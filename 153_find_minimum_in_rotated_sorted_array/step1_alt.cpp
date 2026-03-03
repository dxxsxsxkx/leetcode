#include <vector>
class Solution {
public:
    int findMin(std::vector<int>& nums) {
        if (nums.empty()) {
            return -1;
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
