#include <algorithm>
#include <array>
#include <set>
#include <stack>
#include <utility>
#include <vector>

class Solution {
private:
    std::vector<std::vector<int>>* grid;
    std::set<std::pair<int, int>> visited_lands;
    int height;
    int width;
    int is_land = 1; 

public:
    int maxAreaOfIsland(std::vector<std::vector<int>>& g) {
        grid = &g;
        height = g.size();
        width  = g[0].size();

        int max_area_island = 0; 

        for (int r = 0; r < height; ++r) {
            for (int c = 0; c < width; ++c) {
                if ((*grid)[r][c] == is_land && !visited_lands.contains({r, c})) {
                    int area = measureIsland(r, c);
                    max_area_island = std::max(area, max_area_island); 
                }
            }
        }
        return max_area_island; 
    };

    int measureIsland(int r_start, int c_start) {
        int size_island = 0;
        std::stack<std::pair<int, int>> frontier; 
        frontier.emplace(r_start, c_start); 
        visited_lands.emplace(r_start, c_start);

        std::array<std::pair<int, int>, 4> candidates_direction = {{
            {1, 0}, {0, 1}, {-1, 0}, {0, -1}
        }};

        while (!frontier.empty()) {
            auto [r, c] = frontier.top(); 
            frontier.pop();
            ++size_island;

            for (auto [dr, dc] : candidates_direction) {
                int r_now = r + dr; 
                int c_now = c + dc;

                if (r_now < 0 || r_now >= height) {
                    continue;
                }
                if (c_now < 0 || c_now >= width) {
                    continue;
                }
                if ((*grid)[r_now][c_now] != is_land) {
                    continue; 
                }
                if (visited_lands.contains({r_now, c_now})) {
                    continue;
                }
                frontier.emplace(r_now, c_now);
                visited_lands.emplace(r_now, c_now);
            }
        }
        return size_island; 
    }
};
