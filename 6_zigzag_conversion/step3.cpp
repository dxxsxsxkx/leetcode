#include <numeric>
#include <string>
#include <vector>
class Solution {
public:
    std::string convert(std::string s, int numRows) {
        if (numRows == 1) {
            return s;
        }

        std::vector<std::string> strings_by_line(numRows);
        int line = 0;
        int direction = 1;

        for (char ch : s) {
            strings_by_line[line].push_back(ch);
            if (line == 0) {
                direction = 1;
            }
            if (line == numRows - 1) {
                direction = -1;
            }
            line += direction;
        }
        return std::accumulate(strings_by_line.begin(), strings_by_line.end(), std::string());
    }
};
