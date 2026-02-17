#include <limits>
#include <vector>
class Solution {
public:
    int lengthOfLIS(std::vector<int>& nums) {
        std::vector<int> memo_longest_lengths(nums.size(), 1);
        int longest_length = 0;

        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    memo_longest_lengths[i] = std::max(memo_longest_lengths[i], memo_longest_lengths[j] + 1);
                }
            }
            longest_length = std::max(longest_length, memo_longest_lengths[i]);
        }

        return longest_length;
    }
};
