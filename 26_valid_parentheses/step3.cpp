class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> pairs_brackets = {
            {'(', ')'},
            {'{', '}'},
            {'[', ']'}
        };

        for (char c : s) {
            if (pairs_brackets.contains(c)) {
                st.push(c);
                continue;
            }

            if (st.size() == 0) return false;
            if (c != pairs_brackets[st.top()]) return false;
            st.pop();
        }

        if (st.size() != 0) return false;
        return true;
    }
};