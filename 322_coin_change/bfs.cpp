#include <queue>
#include <vector>
class Solution {
public:
    int coinChange(std::add_cv_t<int>& coins, int amount) {     
        if (amount == 0) {
            return 0;
        }
        
        std::vector<bool> visited(amount + 1, false);
        visited[0] = true;

        std::queue<int> sum; 
        sum.push(0);

        int min_num_coins = 0;

        while (!sum.empty()) {
            int size = sum.size();
            min_num_coins++;
            for (int i = 0; i < size; i++) {
                int current_amount = sum.front();
                sum.pop();

                for (auto coin : coins) {
                    int next_sum = current_amount + coin;

                    if (next_sum == amount) {
                        return min_num_coins;
                    }

                    if (next_sum < amount && !visited[next_sum]) {
                        visited[next_sum] = true;
                        sum.push(next_sum);
                    }
                }
            }
        }
        return -1;
    }
};
