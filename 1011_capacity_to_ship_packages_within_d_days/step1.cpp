#include <algorithm>
#include <numeric>
#include <vector>
class Solution {
public:
    int shipWithinDays(std::vector<int>& weights, int days) {
        // Array of capacities
        int left = *std::max_element(weights.begin(), weights.end());  // minimum
        int right = std::accumulate(weights.begin(), weights.end(), 0);  // maximum

        while (left < right) {
            int mid = left + (right - left) / 2;

            // Can you ship `weights` within `days` with `capacity`? 
            if (canShip(weights, days, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
private:
    bool canShip(const std::vector<int>& weights, int days, int capacity) {
        int days_used = 1;
        int sum = 0;

        for (int weight : weights) {
            if (sum + weight > capacity) {
                ++days_used;
                sum = 0;
            }
            sum += weight;
        }

        return days_used <= days;
    }
};
