# Step 1

## 1回目

わからなかった。適切なデータ型を知らないなと思った。

適当なところをスタート地点として、0にぶつかるまで動いてぶつかったら引き返すみたいな操作を想像した。
ただ、これだと最初のスタート位置を決めるところで全要素をみる必要が出てしまいそう。

## 2回目

[参照](https://github.com/potrue/leetcode/pull/18/commits/df31bd1fad5e85040f0f51f0346ea3ae76afe2f1)。

- 2つの動作を切り分ける：島に行って周りを探索する・探索結果を記録する。

### コード

```cpp
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
```

### メモ

- 順番的には explore, record なのに逆に書けないのが面倒くさい。

- `row`, `r`, `r_next` がごっちゃになりそう。あと座標として扱うのであれば x / y でも良い。
その場合、`r_next` は `dy` にすると良い。

# Step 2

## 勉強

DFS (Depth-first search), BFS (Breadth-first search)

- どちらもつながった領域を全て調べるアルゴリズムで、DFSは行けるところまで行く、BFSは近いところから順番に広げるイメージ。近いところに解があるようなケース（e.g., 最短経路探索）ではBFSが良い。

- Stack(LIFO) がDFS、queue(FIFO) がBFSに対応する。

Union find

- [以下](https://github.com/Ryotaro25/leetcode_first60/pull/18/commits/5ef4f552cb2fd95e75b0f67832372b71a80b0c20)のようなイメージ。
> ざっくりとした理解、島を一つのsetとして2つの異なる島が共通部分を持っていればUnionをしてカウントを減らす

```cpp
#include <set>
#include <utility>
#include <vector>

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        int height = grid.size(); 
        int width = grid[0].size(); 

        UnionFind uf(height * width); 
        int land_count = 0; 
        
        auto id = [&](int r, int c) {
            return r * width + c; 
        }; 

        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                if (grid[r][c] == '1') {
                    ++land_count; 

                    if (r + 1 < height && grid[r + 1][c] == '1') {
                        uf.unite(id(r, c), id(r + 1, c)); 
                    }

                    if (c + 1 < width && grid[r][c + 1] == '1') {
                        uf.unite(id(r, c), id(r, c + 1)); 
                    }
                }
            }
        }
        return uf.countDistinctRoots(grid, width); 
    }
private: 
    struct UnionFind {
        vector<int> parent; 
        vector<int> rank; 

        UnionFind(int n) : parent(n), rank(n, 0) {
            for (int i = 0; i < n; i++) {
                parent[i] = i; 
            }
        }

        int findParent(int x) {
            if (parent[x] != x) {
                parent[x] = findParent(parent[x]); 
            }
            return parent[x]; 
        }

        void unite(int a, int b) {
            int parent_a = findParent(a); 
            int parent_b = findParent(b); 
            
            if (parent_a == parent_b) {
                return; 
            }

            if (rank[parent_a] < rank[parent_b]) {
                swap(a, b); 
            };
            parent[parent_b] = parent[parent_a]; 
            if (rank[a] == rank[b])  {
                ++rank[a]; 
            }
        }

        int countDistinctRoots(std::vector<std::vector<char>>& grid, int w) {
            set<int> roots; 
            for (int r = 0; r < grid.size(); ++r) {
                for (int c = 0; c < grid[0].size(); ++c) {
                    if (grid[r][c] == '1') {
                        roots.insert(findParent(r * w + c));
                    }
                }
            }
            return roots.size(); 
        }
    }; 
};
```
 
0 と 1は別の意味（海と島; 隣接座標）で使われるので、前者に名前をつけておくのも良いかも

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/18/commits/5ef4f552cb2fd95e75b0f67832372b71a80b0c20#r1676765150)

再帰的に陸地かどうかを判定する。深いところで stack overflow にはまる可能性がある。

```cpp
#include <set>
#include <utility>
#include <vector>

class Solution {
public:
    int numIslands(std::vector<std::vector<char>>& grid) {
        int height = grid.size(); 
        int width = grid[0].size(); 
        
        std::set<std::pair<int, int>> visited_lands; 
        int num_island = 0; 

        auto exploreIsland = [&](auto&& exploreIsland, int y, int x) -> void {
            std::vector<std::pair<int, int>> candidate_direction = {
                {0, 1}, {1, 0}, 
                {0, -1}, {-1, 0}
            }; 

            if (0 <= y && y < height && 0 <= x && x < width && 
                grid[y][x] == '1' && !visited_lands.contains({y, x})) {

                visited_lands.emplace(y, x); 
                for (auto [dy, dx] : candidate_direction) {
                    exploreIsland(exploreIsland, y + dy, x + dx);
                }
            }
        }; 
        
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grid[y][x] == '1' && !visited_lands.contains({y, x})) {
                    exploreIsland(exploreIsland, y, x); 
                    ++num_island; 
                }
            }
        }
        return num_island; 
    }
};
```

- [参照](https://github.com/Ryotaro25/leetcode_first60/blob/5ef4f552cb2fd95e75b0f67832372b71a80b0c20/NumberofIslands/step1.cpp)。

# Step 3

問題なくかけた。
