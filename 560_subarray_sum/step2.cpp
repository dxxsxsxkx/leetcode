#include <map>
#include <vector>

class Solution {
public:
    int subarraySum(std::vector<int>& nums, int k) {
        std::map<int, int> prefix_count; 
        prefix_count[0] = 1; 
        
        int sum = 0; 
        int answer = 0; 

        for (int num : nums) {
            sum += num; 
            if (prefix_count.contains(sum - k)) {
                answer += prefix_count[sum - k]; 
            }
            prefix_count[sum]++; 
        }
        return answer; 
    }
};
