#include <vector>
class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int begin = 0; 
        int end = nums.size() - 1;
        int last_num = nums.back();
        
        while (begin <= end) {
            int mid = begin + (end - begin) / 2;

            if (nums[mid] == target) {
                return mid;
            }

            bool midInLHS = (nums[mid] > last_num);
            bool targetInLHS = (target > last_num); 

            if (midInLHS == targetInLHS) {
                if (nums[mid] > target) {
                    end = mid - 1;
                } else {
                    begin = mid + 1;
                }
            } else {
                if (midInLHS) {
                    begin = mid + 1;
                } else {
                    end = mid - 1;
                }
            }
        }

        return -1;
    }
};
