#include <vector>
class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> all_combinations;
        std::vector<int> current_combination;
        findCombinations(candidates, target, 0, current_combination, all_combinations);
        return all_combinations;
    }
private:
    void findCombinations(
        const std::vector<int>& candidates, 
        int target, 
        int start,
        std::vector<int>& current_combination,
        std::vector<std::vector<int>>& all_combinations
    ) {
        if (target == 0) {
            all_combinations.push_back(current_combination);
            return;
        }
        if (target < 0) {
            return;
        }

        for (int i = start; i < candidates.size(); ++i) {
            current_combination.push_back(candidates[i]);
            findCombinations(candidates, target - candidates[i], i, current_combination, all_combinations);
            current_combination.pop_back();
        }
    }
};
