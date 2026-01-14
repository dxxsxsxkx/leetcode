#include <map>
#include <string>

class Solution {
public:
    int firstUniqChar(std::string s) {
        std::map<char, int> char_to_count;
        for (int i = 0; i < s.size(); i++) {
            char_to_count[s[i]]++;
        }

        for (int i = 0; i < s.size(); i++) {
            if (char_to_count[s[i]] == 1) {
              return i;
            }
        }
        return -1;
    }
};
