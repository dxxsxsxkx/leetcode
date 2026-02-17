#include <limits>
#include <vector>
class Solution {
public:
    int lengthOfLIS(std::vector<int>& nums) {
        std::vector<int> min_tails;
        
        for (auto num : nums) {
            auto it = std::lower_bound(min_tails.begin(), min_tails.end(), num); 
            if (it == min_tails.end()) {
                min_tails.push_back(num);
            } else {
                *it = num;
            }
        }
        return min_tails.size();
    }
};
