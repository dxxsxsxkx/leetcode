#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::array<int, 26>, std::vector<std::string>, ArrayHash> counts_to_strings; 
        for (std::string& str : strs) {
            std::array<int, 26> count = {}; 
            for (char ch : str) {
                count[ch - 'a']++; 
            }
            counts_to_strings[count].push_back(std::move(str)); 
        }

        std::vector<std::vector<std::string>> anagrams; 
        for (auto& [key, value] : counts_to_strings) {
            anagrams.push_back(std::move(value)); 
        }
        return anagrams; 
    } 
private: 
    struct ArrayHash {
        size_t operator()(const std::array<int, 26>& counts_alphabets) const {
            size_t result = 0; 
            for (int counts : counts_alphabets) {
                result = result * 31 + counts; 
            }
            return result; 
        }
    }; 
};
