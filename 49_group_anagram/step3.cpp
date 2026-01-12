#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> element_to_strings; 

        for (int i = 0; i < strs.size(); i++) {
            std::string str = strs[i]; 
            std::sort(str.begin(), str.end()); 
            element_to_strings[str].push_back(std::move(strs[i])); 
        }

        std::vector<std::vector<std::string>> anagrams; 
        for (auto& [key, value] : element_to_strings) {
            anagrams.push_back(std::move(value)); 
        }

        return anagrams; 
    }
};
