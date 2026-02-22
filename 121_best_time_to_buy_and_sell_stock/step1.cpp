#include <vector>
class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.size() == 1) {
            return 0;
        }
        return _helper(prices, 0, prices.size() - 1);
    }
private: 
    int _helper(const std::vector<int>& prices, int start, int end) {
        if (start >= end) {
            return 0;
        }
        
        int mid = start + (end - start) / 2;

        int max_return_left = _helper(prices, start, mid);
        int max_return_right = _helper(prices, mid + 1, end);
        
        int min_left = prices[start];
        for (int i = start; i <= mid; i++) {
            min_left = std::min(min_left, prices[i]);
        }

        int max_right = prices[mid]; 
        for (int i = mid + 1; i <= end; i++) { 
            max_right = std::max(max_right, prices[i]); 
        }
        
        return std::max({max_return_left, max_return_right, max_right - min_left});
    }
};
