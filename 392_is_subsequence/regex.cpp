// TLE'd
#include <regex>
#include <string>

class Solution {
public:
    bool isSubsequence(std::string s, std::string t) {
        std::string pattern;
        for (char c : s) {
            pattern += c;
            pattern += ".*";
        }

        std::regex re(pattern);
        return std::regex_search(t, re);
    }
};
