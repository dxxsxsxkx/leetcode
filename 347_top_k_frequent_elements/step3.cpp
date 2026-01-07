#include <map>
#include <vector>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> count_to_value; 
        map<int, vector<int>, greater<int>> value_to_count; 

        for (int num : nums) {
            count_to_value[num]++; 
        }

        for (auto &[count, value] : count_to_value) {
            value_to_count[value].push_back(count);
        }

        vector<int> top_k_frequent; 
        while (value_to_count.size() != 0 && k > 0) {
            auto it = value_to_count.begin(); 

            for (int value : it->second) {
                top_k_frequent.push_back(value); 
                k--; 
            }

            value_to_count.erase(it); 
        }

        return top_k_frequent; 
    }
};
