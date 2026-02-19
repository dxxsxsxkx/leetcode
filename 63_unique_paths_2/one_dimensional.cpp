#include <vector>
class Solution {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        int num_row = obstacleGrid.size();
        int num_col = obstacleGrid[0].size();
        
        std::vector<int> unique_paths_by_row(num_col);
        unique_paths_by_row.front() = 1;
        
        for (int row = 0; row < num_row; row++) {
            for (int column = 0; column < num_col; column++) {
                if (obstacleGrid[row][column] == obstacle_exists) {
                    unique_paths_by_row[column] = 0;
                    continue;
                }
                if (column > 0) {
                    unique_paths_by_row[column] += unique_paths_by_row[column - 1];
                }
            }
        }
        return unique_paths_by_row.back();
    }
private:
    static constexpr int obstacle_exists = 1;
};
