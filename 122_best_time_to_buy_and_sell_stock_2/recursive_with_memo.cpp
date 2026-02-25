#include <vector>
class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }
        memo.assign(prices.size(), std::vector<int>(2, -1));
        return _helper(prices, 0, false);
    }
public: 
    std::vector<std::vector<int>> memo; 

    int _helper(std::vector<int>& prices, int current_time, bool is_holding) {
        if (current_time == prices.size()) {
            return 0;
        }

        if (memo[current_time][is_holding] != -1) {
            return memo[current_time][is_holding];
        }

        int result;
        if (is_holding) {  // do nothing or sell
            result = std::max(
                _helper(prices, current_time + 1, true), 
                prices[current_time] + _helper(prices, current_time + 1, false)
            );
        } else {  // do nothing or buy
            result = std::max(
                _helper(prices, current_time + 1, false),
                -prices[current_time] + _helper(prices, current_time + 1, true)
            );
        }

        return memo[current_time][is_holding] = result;
    }
};
