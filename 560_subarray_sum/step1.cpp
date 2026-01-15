#include <map>
#include <vector>

class Solution {
public:
    int subarraySum(std::vector<int>& nums, int k) {
        std::map<int, int> sum_to_count; 
        for (int i = 0; i < nums.size(); i++) {
            sum_to_count[nums[i] + nums[i + 1]]++; 
            if (i == 0 || i == nums.size() - 1) {
                sum_to_count[nums[i]]++; 
            }
        }

        return sum_to_count[k]; 
    }
};
