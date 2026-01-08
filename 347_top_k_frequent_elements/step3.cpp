#include <map>
#include <vector>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> value_to_count; 
        map<int, vector<int>, greater<int>> count_to_values; 

        for (int num : nums) {
            value_to_count[num]++; 
        }

        for (auto &[value, count] : value_to_count) {
            count_to_values[count].push_back(value);
        }

        vector<int> top_k_frequent; 
        while (!count_to_values.empty() && k > 0) {
            auto it = count_to_values.begin(); 

            for (int value : it->second) {
                top_k_frequent.push_back(value); 
                k--; 
            }

            count_to_values.erase(it); 
        }

        return top_k_frequent; 
    }
};
