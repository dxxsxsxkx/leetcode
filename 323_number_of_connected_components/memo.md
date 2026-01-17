# Step 1

LeetCode の問題はプレミアム限定なので NeetCode の問題で代替する。

## 1回目

島を探すのと同じっぽい（海がないのが違う）。

ノードを端から見ていく。既に見たノードでなければ記録した上で connected component のカウントを一つ増やし、
隣のノードとの間にエッジがあるかどうかを確認し、あれば記録しておく。これを未達のノード全てについて行う。

隣接ノードとの間にエッジがあるかを判定するところでつまづいた。

## 2回目

切り分けて書くことにした。次のノードを調べる部分と、今のノードと次のノードがつながっているかを判定する部分を作った。

### コード

ノード数を $n$、エッジ数を $e$ として、

- 時間計算量：$O(n^2 e)$。`countComponents` のループ・隣接するノードの探索に加え、`isConnected` の探索で e が入る。

- 空間計算量：$O(n)$。ノードを記録していくぶん。

```cpp
#include <set>
#include <stack>
#include <vector>

class Solution {
public:
    int n;
    std::vector<std::vector<int>>* edges;
    std::set<int> checked_nodes;

    int countComponents(int n_, std::vector<std::vector<int>>& edges_) {
        n = n_;
        edges = &edges_;
        
        int n_components = 0;
        for (int i = 0; i < n; ++i) {
            if (!checked_nodes.contains(i)) {
                exploreNode(i);
                ++n_components;
            }
        }
        return n_components;
    };

    bool isConnected(int node_a, int node_b) {
        for (auto& e : *edges) {
            if (e[0] == node_a && e[1] == node_b) {
                return true;
            }
            if (e[0] == node_b && e[1] == node_a) {
                return true;
            }
        }
        return false;
    }

    void exploreNode(int node_start) {
        std::stack<int> frontier;
        frontier.emplace(node_start);
        checked_nodes.emplace(node_start);
        
        while (!frontier.empty()) {
            int node_now = frontier.top();
            frontier.pop();
            for (int j = 0; j < n; ++j) {
                if (!checked_nodes.contains(j) && isConnected(node_now, j)) {
                    checked_nodes.emplace(j);
                    frontier.emplace(j);
                }
            }
        }
    }
};
```

# Step 2

スレッドセーフを意識すると、`step1.cpp` は次のように書き換えられる。

```cpp
#include <set>
#include <stack>
#include <vector>

class Solution {
public:
    int countComponents(int n, std::vector<std::vector<int>>& edges) {
        std::set<int> checked_nodes;

        int n_components = 0;
        for (int i = 0; i < n; ++i) {
            if (!checked_nodes.contains(i)) {
                exploreNode(i, n, checked_nodes, edges);
                ++n_components;
            }
        }
        return n_components;
    }

private: 
    bool isConnected(
      int node_a, 
      int node_b, 
      std::vector<std::vector<int>>& list_edges
    ) {
        for (auto& e : list_edges) {
            if (e[0] == node_a && e[1] == node_b) {
                return true;
            }
            if (e[0] == node_b && e[1] == node_a) {
                return true;
            }
        }
        return false;
    }

    void exploreNode(
      int node_start,
      int n_total_nodes,
      std::set<int>& checked_nodes,
      std::vector<std::vector<int>>& edges
    ) {
        std::stack<int> frontier;
        frontier.emplace(node_start);
        checked_nodes.emplace(node_start);
        
        while (!frontier.empty()) {
            int node_now = frontier.top();
            frontier.pop();
            for (int j = 0; j < n_total_nodes; ++j) {
                if (checked_nodes.contains(j)) {
                    continue;
                }
                if (isConnected(node_now, j, edges)) {
                    checked_nodes.emplace(j);
                    frontier.emplace(j);
                }
            }
        }
    }
};
```

- [前の問題へのコメント](https://github.com/dxxsxsxkx/leetcode/pull/18#discussion_r2700809191)。
確かにそうで、同じコメントは前にももらった。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/20#discussion_r1687455278)。

Union find。イメージとしては、
> コンポーネントの集合体を作ってその数だけNから引くことで答えが出る
というもの。
つまり、エッジで二つのノードが繋がれるたびに独立したコンポーネントは小さくなっていくということ。

- 共通の親ノードを持つノードの集合の数を数える、という話なのでしっくりくる。
書いてみたが難しく、ちょこちょこ引っかかる。

```cpp
class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;

    int FindParent(int x) {
        if (x != parent[x]) {
            parent[x] = FindParent(parent[x]);
        }
        return x;
    }

public:
    UnionFind(int size) : parent(size), rank(size, 1) {
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    bool Union(int x, int y) {
        int parent_x = FindParent(x);
        int parent_y = FindParent(y);

        if (parent_x == parent_y) {
            return false;
        }

        if (rank[parent_x] > rank[parent_y]) {
            parent[parent_y] = parent_x;
        } else if (rank[parent_y] > rank[parent_x]) {
            parent[parent_x] = parent_y;
        } else {
            parent[parent_y] = parent_x;
            ++rank[parent_x];
        }

        return true;
    }
};

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        UnionFind node_tree = UnionFind(n);

        int n_components = n;
        
        for (auto edge : edges) {
            if (node_tree.Union(edge[0], edge[1])) {
                --n_components;
            }
        }

        return n_components;
    }
};

```

- [Path compression](https://github.com/Ryotaro25/leetcode_first60/pull/20/commits/089a63146ae0334f0d1320b47fd2b7ce30674599#r1685633001): 親ノードを書き換えていくことで、直接親ノードを返せるようにする。

リストを使って隣接ノードを管理する。これによって探索する対象を事前に絞り込める。

```cpp
std::vector<std::vector<int>> adjacency_list(n);

for (auto edge : edges) {
  adjacency_list[edge[0]].push_back(edge[1]);
  adjacency_list[edge[1]].push_back(edge[0]);
}
```

- [参照](https://github.com/kazukiii/leetcode/pull/20/commits/28058ff6931878da5ae43a6c5c5e7deed4afdbb6)。

# Step 3

書けた。
