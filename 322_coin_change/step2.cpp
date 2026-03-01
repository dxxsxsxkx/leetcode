#include <vector>
class Solution {
public:
    int coinChange(std::vector<int>& coins, int target_amount) {
        int NOT_FOUND = std::numeric_limits<int>::max() / 2;
        std::vector<int> memo(target_amount + 1, NOT_FOUND);
        memo[0] = 0;

        for (int amount = 1; amount <= target_amount; amount++) {
            for (auto coin : coins) {
                if (amount >= coin) {
                    memo[amount] = std::min(memo[amount], memo[amount - coin] + 1);
                }
            }
        }

        return memo[target_amount] == NOT_FOUND? -1 : memo[target_amount];
    }
};
