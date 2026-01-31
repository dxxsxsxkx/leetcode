# Step 1

## 1回目

前の問題と同じように書いて、level の偶奇によって処理を変えるイメージ。

### コード

おそらく処理が逆になっている。`current_level` を使っているので自分でも混乱した。`next_level = current_level + 1` として、その偶奇で判定するように変える。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root) {
            return {};
        }

        std::vector<std::vector<int>> level_sorted_values;
        std::queue<NodeAndLevel> nodes_to_visit;
        nodes_to_visit.emplace(root, 0);

        while (!nodes_to_visit.empty()) {
            auto [node, current_level] = nodes_to_visit.front();
            nodes_to_visit.pop();

            while (current_level >= level_sorted_values.size()) {
                level_sorted_values.emplace_back();
            }
            level_sorted_values[current_level].emplace_back(node->val);

            if (current_level % 2 == 0) {
                if (node->left) {
                    nodes_to_visit.emplace(node->left, current_level + 1);
                }
                if (node->right) {
                    nodes_to_visit.emplace(node->right, current_level + 1);
                }
            } else {
                if (node->right) {
                    nodes_to_visit.emplace(node->right, current_level + 1);
                }
                if (node->left) {
                    nodes_to_visit.emplace(node->left, current_level + 1);
                }                
            }
            
        }

        return level_sorted_values;
    }
private:
    struct NodeAndLevel {
        TreeNode* node;
        int level;
    };
};
```

### メモ

- ひっくり返しても通っていない。BFS の仕様を理解していないっぽい
  - 同じ level の中では、queue に入れた順番通りに帰ってくるとは限らない？

- 普通に入れたあとで、level の偶奇に応じて reverse する、あるいは `deque` を使って `push_back` / `push_front` を使い分ける。
  - [`std::deque`](https://en.cppreference.com/w/cpp/container/deque.html)：double-ended queue

## 2回目

### コード

`step1.cpp` に書いた。

# Step 2

## 勉強

`reverse` を使って右から追加する・左から追加するという区別ができる。`step2_reverse.cpp` に書いた。

- [参照](https://github.com/fhiyo/leetcode/pull/29/changes/2b87eb71a099fd4577dcd772744274815431ad90)

- ベクトルの反転を `while` の中でやるべきかどうかについては[議論](https://github.com/nittoco/leetcode/pull/34/changes/eb3daf8e998cf5b6d02040e8b115f90d2e00f72a#r1736005119)がある。可読性の問題。

`deque` を使った方法も `step2_deque.cpp` に書いた。

個人的には構造体と for loop を使って書いた方が見た目上はシンプルに見えるが、これはこの書き方に慣れているからかもしれない。

- あと、操作として直感的なのは都度都度ひっくり返す方かも。

# Step 3

結局、もとのコードで書いた。
