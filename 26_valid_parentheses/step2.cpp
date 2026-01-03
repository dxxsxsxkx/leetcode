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
                continue;
            }
            if (st.size() == 0) return false;
            if (pairs_parentheses[st.top()] != c) return false; 
            st.pop();
        }

        if (st.size() != 0) return false;
        return true;
    }
};