class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> pairs_parentheses = {
            {'(', ')'},
            {'{', '}'},
            {'[', ']'}
        };

        for (char c : s) {
            if (pairs_parentheses.contains(c)) {
                st.push(c);
            } else {
                if (st.size() == 0) return false;
                if (c == pairs_parentheses[st.top()]) {
                    st.pop();
                } else {
                    return false;
                }
            }
        }

        if (st.size() != 0) return false;
        return true;
    }
};