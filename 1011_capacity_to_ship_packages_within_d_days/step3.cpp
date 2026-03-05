#include <algorithm>
#include <numeric>
#include <vector>
class Solution {
public:
    int shipWithinDays(std::vector<int>& weights, int days) {
        /*
        Array of possible capacities; each element is no smaller than individual weights
        Will use binary search to find the smallest capacity 
          with which weights can be shiped within `days`
        */
        int min_capacity = *std::max_element(weights.begin(), weights.end());
        int max_capacity = std::reduce(weights.begin(), weights.end());

        while (min_capacity < max_capacity) {
            int mid = min_capacity + (max_capacity - min_capacity) / 2;
            if (canShip(weights, days, mid)) {
                max_capacity = mid;
            } else {
                min_capacity = mid + 1;
            }
        }
        return min_capacity;
    }
private:
    bool canShip(std::vector<int>& weights, int days, int capacity) {
        int days_spent = 1;
        int sum = 0;

        for (int weight : weights) {
            if (sum + weight > capacity) {  // overload; will continue tomorrow
                ++days_spent;
                sum = 0;
            }
            sum += weight;
        }
        return days_spent <= days;
    }
};
