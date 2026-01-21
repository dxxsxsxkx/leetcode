# Step 1

## 1回目

BFSで解こうと考えた。

- 構造体を作って 1. 一つ目の木のノード、2. 二つ目の木のノード、3. 新しい木のノードを含める。
- `queue` にこの構造体を入れていく。
- 左の枝と右の枝に分けて、一つ目のノードと二つ目のノードに続く葉があるかどうかを見ていく。片方があればそっちの葉を入れる。両方あれば足す。

### コード

死ぬほど冗長だが以下のコードで書いて、runtime errorになった。

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
    struct ThreeNodes {
        TreeNode* node1;
        TreeNode* node2;
        TreeNode* node_new;
    };
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (!root1) {
            return root2;
        }
        if (!root2) {
            return root1;
        }

        int sum_two_nodes = root1->val + root2->val;
        TreeNode* root_new = new TreeNode(sum_two_nodes);

        std::queue<ThreeNodes> visiting;
        visiting.emplace(root1, root2, root_new);

        while (!visiting.empty()) {
            auto [node1, node2, node_new] = visiting.front();
            visiting.pop();

            // lhs node
            if (node1->left && node2->left) {
                node_new->left = new TreeNode(node1->left->val + node2->left->val);
                visiting.emplace(node1->left, node2->left, node_new->left);
            }
            if (node1->left && !node2->left) {
                node_new->left = new TreeNode(node1->left->val);
                visiting.emplace(node1->left, nullptr, node_new->left);
            }
            if (!node1->left && node2->left) {
                node_new->left = new TreeNode(node2->left->val);
                visiting.emplace(nullptr, node2->left, node_new->left);
            }

            // rhs node
            if (node1->right && node2->right) {
                node_new->right = new TreeNode(node1->right->val + node2->right->val);
                visiting.emplace(node1->right, node2->right, node_new->right);
            }
            if (node1->right && !node2->right) {
                node_new->right = new TreeNode(node1->right->val);
                visiting.emplace(node1->right, nullptr, node_new->right);
            }
            if (!node1->right && node2->right) {
                node_new->right = new TreeNode(node2->right->val);
                visiting.emplace(nullptr, node2->right, node_new->right);
            }
        }

        return root_new;
    }
};
```

### メモ

- 例えば、`node1` が `nullptr` の時に `node1->left` にアクセスすることでエラーが出ている。
- 三項演算子を使うことで単純化できる。

## 2回目

### コード

`step1.cpp` に書いたものでとりあえず動いた。めちゃくちゃ遅い。

三項演算子で圧縮するとこうなる。読みづらいのか？どうだろう。

```cpp
// lhs node
TreeNode* left1 = node1 ? node1->left : nullptr;
TreeNode* left2 = node2 ? node2->left : nullptr;

if (left1 || left2) {
    int left_new_val = (left1 ? left1->val : 0) + (left2 ? left2->val : 0);
    node_new->left = new TreeNode(left_new_val);
    visiting.emplace(left1, left2, node_new->left);
}
```

# Step 2

[再帰で書くのが自然](https://github.com/Ryotaro25/leetcode_first60/pull/25/commits/b67018715bbcb6efaa049d09590460cbb23774b1#r1699999525)というコメントがあったので、やってみる。

- `step2.cpp` に書いた。あっさりしている。

新しいノードを作るのか作らないのか。

- 例えば以下のように書くと、使うメモリの量が減る一方で入力（`root1`）が破壊される。

```cpp
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if (!root1 && !root2) {
            return nullptr;
        }
        if (!root1) {
            return root2;
        }
        if (!root2) {
            return root1;
        }

        root1->val = root1->val + root2->val;
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);

        return root1;
    }
};
```

- [参照](https://github.com/fhiyo/leetcode/pull/25/commits/6ede65969e02bab2af69bc65c32f0ae895735076#r1650029841)。

- 別のところで同時に `mergeTrees` を呼ばれると変なことになりそうというのもある。
  - [参照](https://discord.com/channels/1084280443945353267/1252267683731345438/1252591437485441024)。

# Step 3

再帰とBFSと両方書いた。
