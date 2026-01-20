# Step 1

## 1回目

BFSで解く。構造体を作成する。ノードを `queue` に入れながら進んでいって、左も右も `nullptr` になったところで `level` を返す。最後まで返らなかったら0を返す。

### コード

```cpp
#include <queue>
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
    struct NodeAndDepth {
        TreeNode* node;
        int depth;
    };
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        std::queue<NodeAndDepth> visiting;
        visiting.emplace(root, 1);

        while (!visiting.empty()) {
            auto [node, level] = visiting.front();
            visiting.pop();
            
            if (!node->left && !node->right) {
                return level;
            }

            if (node->left) {
                visiting.emplace(node->left, level + 1);
            }
            if (node->right) {
                visiting.emplace(node->right, level + 1);
            }
        }

        return 0;
    }
};
```

# Step 2

呼び方。`auto [node, level] = visiting.front()` としていたが、ここで `std::move` を使うかどうかが論点となる。

- [このコメント](https://github.com/Ryotaro25/leetcode_first60/pull/24#discussion_r1702429444)ではオブジェクトが軽いのでコピーで良いのではといっている。

再帰で書いてみる。基本的には `std::min(左の最短距離, 右の最短距離) + 1` で良い。

- ただし、片側に向かって枝が伸びているようなケースでは厳しい。その場合は伸びている方の枝の最短距離 + 1を返すようにする。
  - [参照](https://github.com/Ryotaro25/leetcode_first60/pull/24/commits/6213daa2774f136bb2205a0cb556d82be1e9468a)。


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
    
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int left_depth = minDepth(root->left);
        int right_depth = minDepth(root->right);

        if (root->left && !root->right) {
            return left_depth + 1;
        }
        if (!root->left && root->right) {
            return right_depth + 1;
        }

        return std::min(left_depth, right_depth) + 1;
    }
};
```

制約について。ノードの数は最大で $10^5$ なので、再帰の回数に気をつける必要がある。

- 最悪ケース（片側に偏った木）では再帰が $10^5$ 回呼ばれる。バランスが取れていると $\log_2N$ として大体17回くらいになるから良いが。
  - [参照](https://github.com/TORUS0818/leetcode/pull/24/commits/160fc18153fd5c9178d80bdd44b823ef0149aef1#r1679710631)。

- `queue` に積むのにも影響するのか考えてみよう。
  - 完全二分木に近い形になると、最悪ケースでは最下層のノード数は $2^{15}$ - $2^{16}$。
  - 構造体でポインタを8b、整数を4bとする。padding（コンパイラの読み書きを助けるために隙間が入れられること）によって16bになる。
  - すると大体800KBくらいになる。

# Step 3

問題なくかけた。
