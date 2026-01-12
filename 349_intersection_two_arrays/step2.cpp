#include <unordered_set>
#include <vector>

class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_set<int> set1(nums1.begin(), nums1.end()); 
        std::unordered_set<int> set2(nums2.begin(), nums2.end()); 

        std::vector<int> nums_intersection; 
        for (int num : set1) {
            if (set2.contains(num)) {
                nums_intersection.push_back(num); 
            }
        }
        return nums_intersection; 
    }
};
