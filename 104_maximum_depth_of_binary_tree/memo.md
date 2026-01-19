# Step 1

## 1回目

数列の問題だと思ったがどう書けば良いのかわからず、考えているうちに5分経った。

### メモ

- `root.size()` でノードの数を数える。
- 最長距離が $k$ の場合のノードの総数 $N_k$ を考える。$k = 1, \dots, K$ について、この数列は初項が1、階差数列が公比2の等比数列になっている。
- $k$項目の値は $N_k = 2^k - 1$ となる。
- この $k$ をどう求めれば良いのかがわからなくなった。

## 2回目

色々と勘違いしていたことに気づく。

- 自分が想像していたのは完全二分木だが、この問題では片側の葉が欠けていることもある。
- `root` はポインタなので `root.size()` はできない。

どうすれば良いか？

- あるノードに視点を置く。左に行くか右に行くかがあり、そのうちの長い方が現時点での最長経路になる。その時点での最長距離は長い方の深さ + 1（今見ているノード）。これを再帰的に繰り返す。

### コード

```cpp
#include <algorithm>
class Solution {
public:
    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int left_depth = maxDepth(root->left);
        int right_depth = maxDepth(root->right);

        return 1 + std::max(left_depth, right_depth);
    }
};
```

# Step 2

BFSで書けるとのことなので書いてみた。`queue` の先頭、つまり前の階層で入れたノード（2つ目であれば`root`のみ）を取り出す。そのノードの先に次の階層があるか（左か右に要素があるか）を確認し、あれば `queue` に入れる。

```cpp
# include <queue>
class Solution {
public:
    struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        std::queue<TreeNode*> next_nodes;
        next_nodes.emplace(root);

        int depth = 0;

        while (!next_nodes.empty()) {
            int n_next_nodes = next_nodes.size();
            ++depth;

            for (int i = 0; i < n_next_nodes; ++i) {
                TreeNode* current_node = next_nodes.front();
                next_nodes.pop();

                if (current_node->left) {
                    next_nodes.emplace(current_node->left);
                }
                if (current_node->right) {
                    next_nodes.emplace(current_node->right);
                }
            }
        }

        return depth;
    }
};
```

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/23/commits/e1d5ecf2a993a33296cc7acb51fd2ae5912286ca)。

- `queue` のサイズを取得するのはあまり一般的でない？

  - [参照](https://github.com/rossy0213/leetcode/pull/10/commits/827bf9f2ed20d4c647561fe9a0d73b761d04564e#r1564601348)
  - そうすると、他の人がいっていたように、構造体を定義して `TreeNode*` と現在の深さの両方を入れておくというのが良いのかも。
  ```cpp
  #include <algorithm>
  #include <queue>
  class Solution {
  public:
      struct NodesAndDepth{
          TreeNode* nodes;
          int depth;
      };

      int maxDepth(TreeNode* root) {
          if (!root) {
              return 0;
          }

          std::queue<NodesAndDepth> next_nodes;
          next_nodes.emplace(root, 1);

          int max_depth = 0;

          while (!next_nodes.empty()) {
              auto [current_node, current_depth] = next_nodes.front();
              next_nodes.pop();

              max_depth = std::max(max_depth, current_depth);

              if (current_node->left) {
                  next_nodes.emplace(current_node->left, current_depth + 1);
              }
              if (current_node->right) {
                  next_nodes.emplace(current_node->right, current_depth + 1);
              }
          }

          return max_depth;
      }
  };
  ```

# Step 3

BFSと再帰と両方練習した。

- `NodesAndDepth` は `NodeAndDepth` でないとおかしいので修正した。

- `int` の初期化とかをちょくちょく忘れてしまう...。
