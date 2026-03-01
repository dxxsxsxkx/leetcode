#include <vector>
class Solution {
public:
    int coinChange(std::vector<int>& coins, int amount) {
        int NOT_FOUND = amount + 1;
        std::vector<int> memo(amount + 1, NOT_FOUND);
        memo[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (auto coin : coins) {
                if (i >= coin) {
                    memo[i] = std::min(memo[i], memo[i - coin] + 1);
                }
            }
        }

        return memo[amount] == NOT_FOUND? -1 : memo[amount];
    }
};
