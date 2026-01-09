#include <map>
#include <vector>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::map<int, int> nums_to_indices; 

        for (int i = 0; i < nums.size(); i++) {
            int diff = target - nums[i]; 
            if (nums_to_indices.contains(diff)) {
                return {i, nums_to_indices[diff]}; 
            }
            nums_to_indices.insert({nums[i], i}); 
        }

        return {}; 
    }
};
