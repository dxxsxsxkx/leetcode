#include <string>
#include <unordered_set>
#include <vector>
class Solution {
public:
    bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
        std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());
        std::vector<bool> memo(s.size() + 1, false);
        memo[0] = true;

        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (memo[j] && dict.contains(s.substr(j, i - j))) {
                    memo[i] = true;
                    break;
                }
            }
        }

        return memo[s.size()];
    }
};
