#include <algorithm>
#include <vector>
class Solution {
public:
    void nextPermutation(std::vector<int>& nums) {
        auto it = std::is_sorted_until(nums.rbegin(), nums.rend()); 

        if (it != nums.rend()) {
            auto it_next = std::upper_bound(nums.rbegin(), it, *it); 
            std::iter_swap(it, it_next);
        }

        std::reverse(nums.rbegin(), it);
    }
};
