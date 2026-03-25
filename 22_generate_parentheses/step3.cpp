#include <string>
#include <vector>
class Solution {
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> all_parentheses;
        std::string current_parenthesis;
        addParenthesis(n, 0, 0, current_parenthesis, all_parentheses);
        return all_parentheses;
    }
private:
    void addParenthesis (
        int n,
        int n_open_used,
        int n_close_used,
        std::string& current_parenthesis,
        std::vector<std::string>& all_parentheses
    ) {
        if (current_parenthesis.size() == 2 * n) {
            all_parentheses.emplace_back(current_parenthesis);
            return;
        }

        if (n_open_used < n) {
            current_parenthesis.push_back('(');
            addParenthesis(n, n_open_used + 1, n_close_used, current_parenthesis, all_parentheses);
            current_parenthesis.pop_back();
        }

        if (n_close_used < n_open_used) {
            current_parenthesis.push_back(')');
            addParenthesis(n, n_open_used, n_close_used + 1, current_parenthesis, all_parentheses);
            current_parenthesis.pop_back();
        }
    }
};
