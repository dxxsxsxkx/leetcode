#include <algorithm>
#include <vector>
class Solution {
public:
    std::vector<std::vector<int>> permute(vector<int>& nums) {
        std::vector<std::vector<int>> permutations;

        // first permutation
        std::sort(nums.begin(), nums.end());
        permutations.push_back(nums);

        // repeatedly find next largest permutation
        while (next_permutation(nums.begin(), nums.end())) {
            permutations.push_back(nums);
        }

        return permutations;
    }
};
