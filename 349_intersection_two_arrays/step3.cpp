#include <unordered_set>
#include <utility>
#include <vector>

class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_set<int> set1(nums1.begin(), nums1.end()); 
        std::unordered_set<int> set2(nums2.begin(), nums2.end()); 
        std::vector<int> intersection; 
        if (set1.size() > set2.size()) {
            std::swap(set1, set2); 
        }

        for (int num1 : set1) {
            if (set2.contains(num1)) {
                intersection.push_back(num1); 
            }
        }
        return intersection; 
    }
};
