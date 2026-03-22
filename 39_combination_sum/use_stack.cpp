#include <stack>
#include <vector>
class Solution {
public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> all_combinations;
        std::stack<CombinationAndTargetAndStart> state;
        state.push({{}, target, 0});

        while (!state.empty()) {
            auto [combination, remaining, start] = state.top();
            state.pop();

            if (remaining == 0) {
                all_combinations.push_back(std::move(combination));
                continue;
            }

            if (remaining < 0) {
                continue;
            }

            for (int i = start; i < candidates.size(); ++i) {
                std::vector<int> next_combination = combination;
                next_combination.push_back(candidates[i]);
                state.push({next_combination, remaining - candidates[i], i});
            }
        }

        return all_combinations;
    }
private:
    struct CombinationAndTargetAndStart {
        std::vector<int> combination;
        int target;
        int start_index;
    };
};
