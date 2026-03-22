#include <vector>
class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        return findCombinations(candidates, target, 0);
    }
private:
    std::vector<std::vector<int>> findCombinations(
        const std::vector<int>& candidates, 
        int target, 
        int start
    ) {
        if (target == 0) {
            return {{}};
        }
        if (target < 0) {
            return {};
        }

        std::vector<std::vector<int>> all_combinations;

        for (int i = start; i < candidates.size(); ++i) {
            int candidate = candidates[i];
            int remaining = target - candidate;

            auto combinations_from_remains = findCombinations(candidates, remaining, i);

            for (auto& c : combinations_from_remains) {
                c.push_back(candidate);
                all_combinations.push_back(std::move(c));
            }
        }
        return all_combinations;
    }
};
