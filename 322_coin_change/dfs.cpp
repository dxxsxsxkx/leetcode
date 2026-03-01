#include <stack>
#include <vector>
class Solution {
public:
    int coinChange(std::vector<int>& coins, int amount) {
        if (amount < 0) {
            return -1;
        }
        if (amount == 0) {
            return 0;
        }

        std::vector<int> min_coins(amount + 1, std::numeric_limits<int>::max());

        std::vector<int> sorted_coins;
        for (auto coin : coins) {
            if (coin > amount) {
                continue;
            }
            sorted_coins.push_back(coin);
        }
        sort(sorted_coins.begin(), sorted_coins.end());

        std::stack<std::pair<int, int>> coin_and_sum;
        coin_and_sum.push({0, 0});

        while (!coin_and_sum.empty()) {
            auto [num_coins, sum] = coin_and_sum.top();
            coin_and_sum.pop();

            if (sum > amount || num_coins >= min_coins[sum]) {
                continue;
            }

            min_coins[sum] = num_coins;
            
            for (auto coin : sorted_coins) {
                coin_and_sum.push({num_coins + 1, coin + sum});
            }
        }

        return min_coins.back() == std::numeric_limits<int>::max()? -1 : min_coins.back();
    }
};
