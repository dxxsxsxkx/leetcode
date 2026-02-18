#include <vector>
class Solution {
public:
    int uniquePaths(int m, int n) {
        std::vector<std::vector<int>> table_unique_paths(m, std::vector<int>(n));
        table_unique_paths[0][0] = 1;

        for (int row = 0; row < m; row++) {
            for (int column = 0; column < n; column++) {
                if (row > 0) {
                    table_unique_paths[row][column] += table_unique_paths[row - 1][column];
                }
                if (column > 0) {
                    table_unique_paths[row][column] += table_unique_paths[row][column - 1];
                }
            }
        }

        return table_unique_paths.back().back();
    }
};
