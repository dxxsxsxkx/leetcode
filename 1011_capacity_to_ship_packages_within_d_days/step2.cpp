#include <algorithm>
#include <numeric>
#include <vector>
class Solution {
public:
    int shipWithinDays(std::vector<int>& weights, int days) {  
        /* 
        Array of possible capacities; elements are no smaller than individual weight
        Will use binary search to determine the first capacity
          with which weights can be shiped within `days`
        */
        int min_capacity = *std::max_element(weights.begin(), weights.end());
        int max_capacity = std::reduce(weights.begin(), weights.end());

        while (min_capacity < max_capacity) {
            int mid = min_capacity + (max_capacity - min_capacity) / 2;

            // Can you ship `weights` within `days` with `capacity`? 
            if (canShip(weights, days, mid)) {
                max_capacity = mid;
            } else {
                min_capacity = mid + 1;
            }
        }
        return min_capacity;
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
