#include <algorithm>
#include <vector>
class Solution {
public:
    int uniquePaths(int m, int n) {
        std::vector<int> num_paths_by_row(n, 1);

        for (int row = 1; row < m; row++) {
            std::vector<int> next_num_paths_by_row(n);
            next_num_paths_by_row[0] = 1;
            for (int col = 1; col < n; col++) {
                next_num_paths_by_row[col] = num_paths_by_row[col] + next_num_paths_by_row[col - 1];
            }
            std::swap(num_paths_by_row, next_num_paths_by_row);
        }
        return num_paths_by_row[n - 1];
    }
};
