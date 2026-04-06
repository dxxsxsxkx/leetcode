#include <string>
#include <vector>
class Solution {
public:
    std::string convert(std::string s, int numRows) {
        if (numRows == 1) {
            return s;
        }
        
        int cycle = 2 * numRows - 2;
        int numCols = (s.size() / cycle + 1) * (numRows - 1);
        std::vector<std::vector<char>> zigzag_table(
            numRows, 
            std::vector<char>(numCols, ' ')
        ); 
        int r = 0;
        int c = 0;
        bool going_down = true;

        for (char ch : s) {
            zigzag_table[r][c] = ch;

            if (going_down) {
                if (r == numRows - 1) {
                    going_down = false;
                    --r; 
                    ++c;
                } else {
                    ++r;
                }
            } else {
                if (r == 0) {
                    going_down = true;
                    ++r;
                } else {
                    --r;
                    ++c;
                }
            }
        }
        
        // Read the table created above
        std::string zigzag_s; 
        for (r = 0; r < numRows; ++r) {
            for (c = 0; c < numCols; ++c) {
                if (zigzag_table[r][c] != ' ') {
                    zigzag_s += zigzag_table[r][c];
                }
            }
        }

        return zigzag_s;
    }
};
