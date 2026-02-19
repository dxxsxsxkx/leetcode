#include <vector>
class Solution {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        int num_row = obstacleGrid.size();
        int num_col = obstacleGrid[0].size();
        std::vector<std::vector<int>> unique_paths(num_row, std::vector<int>(num_col));

        unique_paths[0][0] = 1;

        for (int row = 0; row < num_row; row++) {
            for (int column = 0; column < num_col; column++) {
                if (obstacleGrid[row][column] == 1) {
                    unique_paths[row][column] = 0;
                    continue;
                }

                if (row > 0) {
                    unique_paths[row][column] += unique_paths[row - 1][column];
                }
                if (column > 0) {
                    unique_paths[row][column] += unique_paths[row][column - 1];
                }
            }
        }

        return unique_paths.back().back();
    }
};
