# Step 1

## 1回目

Number of Islands と同様の方針で考える。
途中まで書いたところでメンバ変数の扱いがわからなくなり、答えを見た。

- DFSでやる。未探索の陸地を見つけたら探索する（`measureIsland`）。

  - 初期地点ではサイズ0として、探索して陸地にあたるごとにサイズを1ずつ増やしていく。厳密には陸地であれば `stack` に入れる → 次のステップでその分のカウントを増やすという順番になっている。

- 探索が終わったら、現時点での最大の陸地サイズと探索結果とを比較して大きい方をとる。

- 最後に最大の陸地サイズを返す。

### コード

```cpp
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
```

### メモ

- 前回はラムダ関数で書いていたものをメンバとして持つように変えた。
引数が増えすぎるのが気持ち悪かったので色々分けて持たせたが、やりすぎかも？

  - この辺の感覚がまだない。

- Early return. 

## 2回目

書けた。時間がかかる。

# Step 2

`set<pair<int, int>>` の代わり

- [参照](https://github.com/colorbox/leetcode/pull/32/commits/9e158c529cc75864b1ecad429cecfbe15e0723a0#r1898177664)。速度と見やすさのトレードオフ。

- `vector<vector<bool>> visited(row_count, vector<bool>(col_count, false));` としている人もいた。真偽値の行列を持っておく感じ。`grid[r][c]`と対応するのでわかりやすい気もする。

定数

- [スタイルガイド](https://google.github.io/styleguide/cppguide.html#Constant_Names)より。`kLand` とかで良さそう。

- `const int kLand = 1;` あるいは `static constexpr int kLand = 1;`。

  - [参照]((https://github.com/Ryotaro25/leetcode_first60/pull/19#discussion_r1681035002))。`constexpr` はコンパイル時に値が決まる。`const` は変更できないだけ。

後で Union find も書こうと思う。

# Step 3

書けた。
