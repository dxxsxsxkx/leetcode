#include <map>
#include <string>
#include <vector>

class Solution {
public:
    int firstUniqChar(std::string s) {
        std::map<char, std::vector<int>> char_to_indices; 
        for (int i = 0; i < s.size(); i++) {
            char char_i = s[i]; 
            char_to_indices[char_i].push_back(i); 
        }

        int idx_smallest = 100000 + 1; 
        for (auto& [key, value] : char_to_indices) {
            if (value.size() == 1 && value[0] < idx_smallest) {
                idx_smallest = value[0]; 
            }
        }

        if (idx_smallest == 100001) {
            idx_smallest = -1; 
        }
        return idx_smallest; 
    }
};
