#include <algorithm>
#include <unordered_set>
class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        std::unordered_set<char> characters;
        
        int left = 0;
        int max_length = 0;

        for (int right = 0; right < s.size(); ++right) {
            while (characters.contains(s[right])) {
                characters.erase(s[left]);
                ++left;
            }
            characters.insert(s[right]);
            max_length = std::max<int>(max_length, characters.size());
        }
        return max_length;
    }
};
