#include <vector>
class Solution {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        if (nums.size() == 1) {
            return {nums};
        }

        std::vector<std::vector<int>> permutations;

        for (int i = 0; i < nums.size(); ++i) {
            int first = nums[i];

            std::vector<int> remaining = nums;
            remaining.erase(remaining.begin() + i);

            auto permutations_remain = permute(remaining);

            for (auto p : permutations_remain) {
                p.insert(p.begin(), first);
                permutations.push_back(p);
            }
        }
        return permutations;
    }
};
