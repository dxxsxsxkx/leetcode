#include <vector>
class Solution {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        int num_row = obstacleGrid.size();
        int num_col = obstacleGrid[0].size();

        std::vector<std::vector<int>> unique_paths(num_row, std::vector<int>(num_col));
        unique_paths[0][0] = 1;

        for (int r = 0; r < num_row; r++) {
            for (int c = 0; c < num_col; c++) {
                if (obstacleGrid[r][c] == kObstacle) {
                    unique_paths[r][c] = 0;
                    continue;
                }
                if (r > 0) {
                    unique_paths[r][c] += unique_paths[r - 1][c];
                }
                if (c > 0) {
                    unique_paths[r][c] += unique_paths[r][c - 1];
                }
            }
        }

        return unique_paths.back().back();
    }
private: 
    static constexpr int kObstacle = 1;
};
