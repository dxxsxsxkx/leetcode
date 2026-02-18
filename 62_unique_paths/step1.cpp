#include <vector>
class Solution {
public:
    int uniquePaths(int m, int n) {
        std::vector<std::vector<int>> table_unique_paths(m, std::vector<int>(n));
        table_unique_paths[0][0] = 1;

        for (int row = 0; row < m; ++row) {
            for (int col = 0; col < n; ++col) {
                if (row > 0) {
                    table_unique_paths[row][col] += table_unique_paths[row - 1][col];
                }
                if (col > 0) {
                    table_unique_paths[row][col] += table_unique_paths[row][col - 1];
                }
            }
        }

        return table_unique_paths[m - 1][n - 1];
    }
};
