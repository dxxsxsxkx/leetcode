#include <vector>
class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int pivot = findPivot(nums);

        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int real_mid = (mid + pivot) % nums.size();

            if (nums[real_mid] == target) {
                return real_mid;
            }

            if (nums[real_mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }
private: 
    int findPivot(std::vector<int>& nums) {
        int left = 0; 
        int right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
};
