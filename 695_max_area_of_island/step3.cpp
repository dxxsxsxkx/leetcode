#include <algorithm>
#include <array>
#include <set>
#include <stack>
#include <utility>
#include <vector>

class Solution {
private: 
    std::vector<std::vector<int>>* grid;
    int height;
    int width;
    std::set<std::pair<int, int>> visited_lands;
    static constexpr int kLand = 1;

public:
    int maxAreaOfIsland(std::vector<std::vector<int>>& g) {
        grid = &g;
        height = g.size();
        width = g[0].size();

        int max_size_island = 0;

        for (int r = 0; r < height; ++r) {
            for (int c = 0; c < width; ++c) {
                if ((*grid)[r][c] == kLand && !visited_lands.contains({r, c})) {
                    visited_lands.emplace(r, c);
                    int size_island = measureIsland(r, c);
                    max_size_island = std::max(size_island, max_size_island);
                }
            }
        }

        return max_size_island;
    };

    int measureIsland(int r_start, int c_start) {
        std::stack<std::pair<int, int>> frontier;
        frontier.emplace(r_start, c_start);

        std::array<std::pair<int, int>, 4> candidates_next = {{
            {1, 0}, {0, 1}, {-1, 0}, {0, -1}
        }};

        int size_island = 0;

        while (!frontier.empty()) {
            auto [r, c] = frontier.top();
            frontier.pop();
            ++size_island;

            for (auto [dr, dc] : candidates_next) {
                int r_now = r + dr;
                int c_now = c + dc;

                if (r_now < 0 || r_now >= height) {
                    continue;
                }
                if (c_now < 0 || c_now >= width) {
                    continue;
                }
                if ((*grid)[r_now][c_now] != kLand) {
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
