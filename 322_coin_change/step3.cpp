#include <vector>
class Solution {
public:
    int coinChange(std::vector<int>& coins, int target_amount) {
        int NOT_FOUND = std::numeric_limits<int>::max() / 2;

        std::vector<int> fewest_coins(target_amount + 1, NOT_FOUND);
        fewest_coins[0] = 0;

        for (int amount = 1; amount <= target_amount; amount++) {
            for (auto coin : coins) {
                if (amount >= coin) {
                    fewest_coins[amount] = std::min(fewest_coins[amount], fewest_coins[amount - coin] + 1);
                }
            }
        }

        return fewest_coins[target_amount] == NOT_FOUND? -1 : fewest_coins[target_amount];
    }
};
