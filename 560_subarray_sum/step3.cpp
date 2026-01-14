#include <map>
#include <vector>

class Solution {
public:
    int subarraySum(std::vector<int>& nums, int k) {
        std::map<int, int> cumsum_count; 
        cumsum_count[0] = 1; 
        int cumsum = 0; 
        int count_k = 0; 

        for (int num : nums) {
            cumsum += num; 
            cumsum_count[cumsum]++; 
            if (cumsum_count.contains(cumsum - k)) {
                count_k += cumsum_count[cumsum - k]; 
            }
        }

        return count_k; 
    }
};
