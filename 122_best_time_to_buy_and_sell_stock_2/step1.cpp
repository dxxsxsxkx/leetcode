#include <vector>
class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }

        int profit = 0; 
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] < 0) {
              throw std::invalid_argument("Price must not be negative");
            }
            
            if (prices[i] > prices[i - 1]) {
                profit += prices[i] - prices[i - 1];
            }
        }
        return profit; 
    }
};
