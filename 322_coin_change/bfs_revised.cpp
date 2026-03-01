#include <queue>
#include <vector>
class Solution {
public:
    int coinChange(std::vector<int>& coins, int target_amount) {
        if (target_amount == 0) {
            return 0;
        }
        
        int NOT_FOUND = -1;

        std::vector<bool> visited_amount(target_amount + 1, false);
        visited_amount[0] = true;

        std::queue<int> amounts; 
        amounts.push(0);

        int min_num_coins = 0;

        while (amounts.empty()) {
            int size = amounts.size();
            min_num_coins++; 

            for (int level = 0; level < size; level++) {
                int amount = amounts.front();
                amounts.pop();

                for (auto coin : coins) {
                    int next_amount = amount + coin; 
                    if (next_amount == target_amount) {
                        return min_num_coins;
                    }
                    if (next_amount < target_amount && !visited_amount[next_amount]) {
                        visited_amount[next_amount] = true;
                        amounts.push(next_amount);
                    }
                }
            }
        }

        return NOT_FOUND;
    }
};
