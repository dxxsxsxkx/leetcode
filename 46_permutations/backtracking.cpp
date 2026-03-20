#include <algorithm>
#include <vector>
class Solution {
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> permutations;
        find_permutations(0, nums, permutations);
        return permutations;
    }
private:
    void find_permutations(int start, std::vector<int>& nums, std::vector<std::vector<int>>& result) {
        if (start == nums.size()) {
            result.push_back(nums);
            return;
        }

        for (int i = start; i < nums.size(); ++i) {
            std::swap(nums[start], nums[i]);
            find_permutations(start + 1, nums, result);
            std::swap(nums[start], nums[i]);
        }
    }
};
