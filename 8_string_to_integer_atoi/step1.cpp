#include <cctype>
#include <limits>
#include <string> 
class Solution {
public:
    int myAtoi(std::string s) {
        int i = 0; 

        // 1. ignore whitespaces
        while (i < s.size() && s[i] == ' ') {
            ++i;
        }

        // 2. check the sign
        int sign = 1;
        if (i < s.size() && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-') {
                sign = -1;
            }
            ++i;
        }

        // 3. read digits
        int32_t s_unsigned = 0;
        while (i < s.size() && isdigit(s[i])) {
            int digit = s[i] - '0';
            
            // 4. overflow? 
            if (s_unsigned > std::numeric_limits<int32_t>::max() / 10 ||
                (s_unsigned == std::numeric_limits<int32_t>::max() / 10 && digit > 7)) {
                    return (sign == 1 ? std::numeric_limits<int32_t>::max() : std::numeric_limits<int32_t>::min());
                }

            s_unsigned = s_unsigned * 10 + digit;
            ++i;
        }

        return sign * s_unsigned;
    }
};
