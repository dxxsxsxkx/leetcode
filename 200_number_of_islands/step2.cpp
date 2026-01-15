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

        auto recordIsland = [&](std::stack<std::pair<int, int>>& st, int r_now, int c_now) {
            if (0 <= r_now && r_now < height && 0 <= c_now && c_now < width &&
                grid[r_now][c_now] == '1' &&
                !visited_lands.contains({r_now, c_now})) {
                    st.emplace(r_now, c_now); 
                    visited_lands.emplace(r_now, c_now); 
                }
        }; 

        auto exploreIsland = [&](int r_start, int c_start) {
            std::stack<std::pair<int, int>> frontiers; 
            frontiers.emplace(r_start, c_start); 
            
            std::vector<std::pair<int, int>> candidates_direction = {
                {0, 1}, {1, 0}, 
                {0, -1}, {-1, 0}
            };

            while(!frontiers.empty()) {
                auto [r, c] = frontiers.top(); 
                frontiers.pop(); 
                for (auto [dr, dc] : candidates_direction) {
                    recordIsland(frontiers, r + dr, c + dc); 
                }
            }
        }; 

        int count_islands = 0; 
        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                if (grid[r][c] == '1' && !visited_lands.contains({r, c})) {
                    visited_lands.emplace(r, c); 
                    exploreIsland(r, c); 
                    ++count_islands; 
                }
            }
        }
        return count_islands; 
    }
};
