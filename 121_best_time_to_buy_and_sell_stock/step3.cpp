#include <algorithm>
#include <vector>
class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }

        int current_min_price = prices[0];
        int current_max_return = prices[0] - prices[0];

        for (int i = 0; i < prices.size(); ++i) {
            if (prices[i] < 0) {
                throw std::invalid_argument("Price must be positive");
            }

            current_min_price = std::min(current_min_price, prices[i]);
            current_max_return = std::max(current_max_return, prices[i] - current_min_price);
        }

        return current_max_return;
    }
};
