#include <vector>
class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        if (nums.size() == 0) {
            return {{}};
        }

        std::vector<std::vector<int>> subset;

        int first = nums[0];

        std::vector<int> remaining(nums.begin() + 1, nums.end());

        auto subset_from_remains = subsets(remaining);

        for (auto s : subset_from_remains) {
            subset.push_back(s);
            s.insert(s.begin(), first);
            subset.push_back(s);
        }

        return subset;
    }
};
