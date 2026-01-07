#include <vector>
#include <map>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> value_to_count; 
        map<int, vector<int>, greater<int>> count_to_value; 

        for (int num : nums) {
            value_to_count[num]++; 
        }

        for (auto &[value, count] : value_count) {
            count_to_value[count].push_back(value); 
        }

        vector<int> top_k_frequent; 
        while (count_to_value.size() != 0 && k > 0) {
            auto it = count_to_value.begin(); 

            for (int value : it->second) {
                top_k_frequent.push_back(value); 
                k--;
            }

            count_to_value.erase(it);

        }

        return top_k_frequent; 
    }
};
