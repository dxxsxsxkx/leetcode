#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> nums_to_indices; 

        for (int i = 0; i < nums.size(); i++) {
            int diff = target - nums[i]; 
            if (nums_to_indices.contains(diff)) {
                return {nums_to_indices[diff], i}; 
            }
            nums_to_indices.insert({nums[i], i}); 
        }

        return {}; 
    }
};
