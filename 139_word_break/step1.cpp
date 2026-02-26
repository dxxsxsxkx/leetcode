#include <unordered_set>
#include <string> 
#include <vector>
class Solution {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
        std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end()); 
        std::vector<int> memo(s.size(), NOT_SEEN);
        return _helper(s, 0, dict, memo);
    }
private:
    int NOT_SEEN = -1;

    bool _helper(
      std::string& s, 
      int start, 
      std::unordered_set<std::string>& wordDict, 
      std::vector<int>& memo
    ) {
        if (start == s.size()) {
            return true;
        }

        if (memo[start] != NOT_SEEN) {
            return memo[start];
        }

        std::string strs; 
        for (int i = start; i < s.size(); i++) {
            strs += s[i];
            if (wordDict.contains(strs)) {
                if (_helper(s, i + 1, wordDict, memo)) {
                    return memo[start] = true;
                }
            }
        }

        return memo[start] = false;
    }
};
