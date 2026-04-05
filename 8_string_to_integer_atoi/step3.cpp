#include <cctype>
#include <limits>
#include <string>
class Solution {
public:
    int myAtoi(std::string s) {
        int i = 0; 

        // 1. ignore leading whitespaces
        while (i < s.size() && s[i] == ' ') {
            ++i;
        }

        // 2. determine the sign
        int sign = 1;
        if (i < s.size() && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-') {
                sign = -1;
            }
            ++i;
        }

        // 3. Parse digits
        int s_unsigned = 0;
        while (i < s.size() && isdigit(s[i])) {
            int digit = s[i] - '0';

            // 4. Check for overflow
            if (s_unsigned > std::numeric_limits<int>::max() / 10 ||
                (s_unsigned == std::numeric_limits<int>::max() / 10 && digit > (std::numeric_limits<int>::max() % 10))) {
                    return (sign == 1 ? std::numeric_limits<int>::max() : std::numeric_limits<int>::min());
                }

            s_unsigned = s_unsigned * 10 + digit;
            ++i;
        }

        return sign * s_unsigned;
    }
};
