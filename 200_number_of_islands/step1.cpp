#include <set>
#include <stack>
#include <utility>
#include <vector>

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        int height = grid.size(); 
        int width = grid[0].size(); 

        std::set<std::pair<int, int>> visited_lands; 
        int num_island = 0; 

        auto recordIsland = [&](std::stack<std::pair<int, int>>& st, int row, int col) {
            if (0 <= row && row < height && 0 <= col && col < width && 
                grid[row][col] == '1' && 
                !visited_lands.contains({row, col})) {
                    st.emplace(row, col); 
                    visited_lands.emplace(row, col); 
                }
        }; 

        auto exploreIsland = [&](int row_start, int col_start) {
            // 地図を持っておく
            std::stack<std::pair<int, int>> frontiers; 
            frontiers.emplace(row_start, col_start); 
            visited_lands.emplace(row_start, col_start);

            // 動ける方向
            std::vector<std::pair<int, int>> candidate_direction = {
                {0, 1}, {1, 0}, 
                {0, -1}, {-1, 0}
            }; 

            while (!frontiers.empty()) {
                auto [r, c] = frontiers.top(); 
                frontiers.pop(); 

                for (auto [r_next, c_next] : candidate_direction) {
                    recordIsland(frontiers, r + r_next, c + c_next); 
                }
            }
        }; 

        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                // search for island to visit
                if (grid[r][c] == '1' && !visited_lands.contains({r, c})) {
                    exploreIsland(r, c); 
                    ++num_island; 
                }
            }
        }

        return num_island; 
    }
};
