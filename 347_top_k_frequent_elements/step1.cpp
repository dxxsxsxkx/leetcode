#include 
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> value_count; 
        map<int, vector<int>, greater<int>> count_value; 
        vector<int> top_k_frequent; 

        for (int num : nums) {
            value_count[num]++; 
        }

        for (auto &[value, count] : value_count) {
            count_value[count].push_back(value); 
        }

        for (auto it = count_value.begin(); it != count_value.end() && k > 0; ++it) {
            for (int value : it->second) {
                top_k_frequent.push_back(value);
                k--; 

                if (k == 0) {
                    break;
                }
            }
        }

        return top_k_frequent; 
    }
};
