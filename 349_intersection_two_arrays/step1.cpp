#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_map<int, int> num_to_count_1; 
        std::unordered_map<int, int> num_to_count_2; 
        for (int num1 : nums1) {
            num_to_count_1[num1]++; 
        }
        for (int num2 : nums2) {
            num_to_count_2[num2]++; 
        }

        std::vector<int> nums_intersection; 
        for (auto& [key1, value1] : num_to_count_1) {
            if (num_to_count_2.contains(key1)) {
                nums_intersection.push_back(std::move(key1)); 
            }
        }
        return nums_intersection; 
    }
};
