#include <vector>
class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        std::vector<std::vector<int>> subsets_already_made = {{}};

        for (int num : nums) {
            int current_size = subsets_already_made.size();
            for (int i = 0; i < current_size; ++i) {
                std::vector<int> subset = subsets_already_made[i];
                subset.emplace_back(num);
                subsets_already_made.emplace_back(subset);
            }
        }

        return subsets_already_made;
    }
};
