#include <string>
#include <unordered_set>
#include <vector>
class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        // Duplicates are handled by unordered set
        std::unordered_set<std::string> current_parentheses;
        current_parentheses.insert("()");

        // i refers to the number of pairs already made
        for (int i = 2; i <= n; ++i) {
            std::unordered_set<std::string> next_parentheses;
            for (const auto& p : current_parentheses) {
                for (int j = 0; j <= p.size(); ++j) {
                    std::string new_parenthesis = p.substr(0, j) + "()" + p.substr(j);
                    next_parentheses.insert(new_parenthesis);
                }
            }
            current_parentheses = std::move(next_parentheses);
        }
        return std::vector<std::string>(current_parentheses.begin(), current_parentheses.end());
    }
};
