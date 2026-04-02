#include <string>
class Solution {
public:
    bool isSubsequence(std::string s, std::string t) {
        if (s.size() == 0) {
            return true;
        }
        if (t.size() == 0) {
            return false;
        }

        int s_index = 0;
        for (const auto& ch : t) {
            if (s[s_index] == ch) {
                ++s_index;
            }
            if (s_index == s.size()) {
                return true;
            }
        }
        return false;
    }
};
