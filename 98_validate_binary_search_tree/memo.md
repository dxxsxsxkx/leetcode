# Step 1

## 1回目

再帰で書こうとした。左右の子ノードがあるかどうかを確認し、ある場合にはその値と親ノードの値を比較する。子ノードの値が条件を満たさなかった場合には `false` を返す。

### コード

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
    bool isValidBST(TreeNode* root) {
        if (!root) {
            return false;
        }
        int root_val = root->val;

        if (root->left) {
            int left_val = root->left->val;
            if (root_val <= left_val) {
                return false;
            }
        }

        if (root->right) {
            int right_val = root->right->val;
            if (root_val >= right_val) {
                return false;
            }
        }

        bool left_is_valid = isValidBST(root->left);
        bool right_is_valid = isValidBST(root->right);

        return left_is_valid && right_is_valid;
    }
};
```

### メモ

- 空の木は BST なので `true` を返す必要がある。

- 部分木の全体を見て判断しなければいけないが、このコードでは親子関係のみを見ている。
  - 例えば、`root = [5,4,6,null,null,3,7]` がまずいケース。3 は 5 の右部分木にあるのに、5 よりも小さい。

## 2回目

各部分木において制約条件を保持し続けるようにする。各ノードの値には上下から制約がかかるので、それを両方持っておく。それに合わせて、親子ノードごとで処理をしていたものをノードごとで処理するように変える。

### コード

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
    bool isValidBST(TreeNode* root) {
        if (!root) {
            return true;
        }

        return helper(root, INT_MIN, INT_MAX);
    }
private:
    bool helper(TreeNode* node, int min_val, int max_val) {
        if (!node) {
            return true;
        }

        if (node->val <= min_val || node->val >= max_val) {
            return false;
        }

        bool left_is_valid = helper(node->left, min_val, node->val);
        bool right_is_valid = helper(node->right, node->val, max_val);

        return left_is_valid && right_is_valid;
    }
};
```

### メモ

- `root = [2147483647]` でエラーが出た。`-2^31 <= Node.val <= 2^31 - 1` なので、`int` を使うと境界値に引っかかる。

## 3回目

### メモ

`long` を使って解決。コードは `step1.cpp` に書いた。`long long` でもよくて、その場合は `llong_min` と `llong_max` を使う。

- [Stack overflow](https://ja.stackoverflow.com/questions/45529/c%E8%A8%80%E8%AA%9E%E3%81%A7%E3%81%AEint%E5%9E%8B%E3%81%A8long%E5%9E%8B%E3%81%A8long-long%E5%9E%8B%E3%81%AE%E9%81%95%E3%81%84%E3%81%AB%E3%81%A4%E3%81%84%E3%81%A6)より。`long` や `long long` を具体的にどの大きさにするかは設計者に任されているらしい。型の大きさが特に気になるようなケースではサイズが明示的に定められている `int16_t` などを使う。
  - [参考](https://www.reddit.com/r/arduino/comments/1g5vev/int16_t_what_does_this_mean/?show=original)。

# Step 2

## 勉強

ノード数の最大値が $10^4$ なので片側に偏った場合に stack overflow が起こる可能性がある。今の環境のメモリサイズ的には大丈夫そう。

- [参考](https://github.com/Ryotaro25/leetcode_first60/pull/30/changes/4186dff12ff4a073e2d00ef7a2c6f5ffe1c25b16#r1730248111)

頭から見ていくバージョンもありうる。これを `step2.cpp` に書いた。

- [参考](https://github.com/Ryotaro25/leetcode_first60/pull/30/changes/4186dff12ff4a073e2d00ef7a2c6f5ffe1c25b16#diff-4b719516317cde7637abbe1920012fdba6b17fa530a1e41079a725272c85f645)

[こういう発想](https://github.com/fhiyo/leetcode/pull/30/changes/052994b11f3e92a38b3636466d3eb4c5fe04a77b)はなかった。
> inorder traversalをしたときに、ノードの値が昇順に整列されていれば良い。

- こちらは `step2_inorder.cpp` に書いた。

# Step 3

再帰で書いた。
