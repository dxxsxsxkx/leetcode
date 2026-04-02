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

        int NOT_FOUND = -1;
        int start = 0;
        for (const auto& chr : s) {
            int index = findChr(t, chr, start);
            if (index == NOT_FOUND) {
                return false;
            }
            start = index + 1;;
        }
        return true;
    }
private:
    int findChr(const std::string& t, char target_chr, int start) {
        for (int i = start; i < t.size(); ++i) {
            if (t[i] == target_chr) {
                return i;
            }
        }
        return -1;
    }
};
