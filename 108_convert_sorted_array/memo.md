# Step 1

## 1回目

### コード

`nums` の要素を左から繋げていく？方針が立たなかった。

### メモ

- 平衡木：二分木のうち全てのノードの子ノードの高さが同じもしくは1違うもの。
- このような操作は具体的にはどういうケースで使うのか？
  - 問題ではノードの繋ぎ方には制限がなさそうだが、実際には値に応じて並び替えるなどの操作が必要になりそうな気がする。
  
## 2回目

真ん中の値を root として左右に伸ばしていく。これだと再帰でかける。参照：

- https://github.com/TORUS0818/leetcode/pull/26/changes/a0076ed7fb3d6c7d5410d4f960c6a997d308d054
- https://github.com/Ryotaro25/leetcode_first60/pull/26/changes/fec55572beda70ad8f2239010391a397de95c39a#diff-5b0cab46928ebf03b5bf3aa1d60b9d7eb00c5602272789e27dc83983b86b95a2R11-R13

### コード

`step1.cpp` に書いた。

# Step 2

## 勉強

`const` をつける。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/26/changes/fec55572beda70ad8f2239010391a397de95c39a#diff-5b0cab46928ebf03b5bf3aa1d60b9d7eb00c5602272789e27dc83983b86b95a2)

`nums` の要素が偶数個の場合、`idx_middle` の取り方によって木の形が変わってくる。

- `[-10, -3, 0, 1, 5, 9]` の場合を考えると、`nums.size()` で `1` のインデックスが返り、そこを基準に木が構成される。

半開区間 `idx_start >= idx_end` とすると境界条件をうまく処理できるかも。

BFS でも書ける。新しい木のノード・`nums` の始点 / 終点を三点セットで構造体に持たせる。

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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if (nums.empty()) {
            return nullptr;
        }

        TreeNode* new_root = new TreeNode();
        std::queue<NodeAndIndices> visiting;
        visiting.emplace(new_root, 0, nums.size() - 1);

        while (!visiting.empty()) {
            auto [node, idx_start, idx_end] = visiting.front();
            visiting.pop();

            int idx_middle = (idx_start + idx_end) / 2;
            node->val = nums[idx_middle];

            if (idx_start < idx_middle) {
                node->left = new TreeNode();
                visiting.emplace(node->left, idx_start, idx_middle - 1);
            }

            if (idx_middle < idx_end) {
                node->right = new TreeNode();
                visiting.emplace(node->right, idx_middle + 1, idx_end);
            }
        }
        return new_root;

    }
private:
    struct NodeAndIndices {
        TreeNode* node;
        int idx_start;
        int idx_end;
    };
};
```

- [参照](https://github.com/TORUS0818/leetcode/pull/26/changes/a0076ed7fb3d6c7d5410d4f960c6a997d308d054#diff-f90af665c7c9be35afaf8e105d92ceba0f1c7c14d95fcac6cb0f77d153da311c)

- 上のコードだと、`idx_start <= idx_middle <= idx_end` が `idx_middle` を作った時点で保証され、間に要素があるときだけ `emplace` されるようになっている。

ダミーの値を持った complete binary tree を作っておいて、そこに後から値を入れる方法がある。

```cpp
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // 形だけの完全二分木を作る
        TreeNode* root = buildCompleteBinaryTree(0, nums.size());

        // inorder traversal で値を流し込む
        int index = 0;
        setValueInorder(root, nums, index);

        return root;
    }

private:
    // 完全二分木を作る（値は入れない）
    TreeNode* buildCompleteBinaryTree(int index, int n) {
        if (index >= n) return nullptr;

        TreeNode* node = new TreeNode();
        node->left = buildCompleteBinaryTree(2 * index + 1, n);
        node->right = buildCompleteBinaryTree(2 * index + 2, n);
        return node;
    }

    // inorder traversal で nums を順に代入
    void setValueInorder(TreeNode* root, vector<int>& nums, int& index) {
        if (!root) return;

        // 左 → 根 → 右 で入れている
        setValueInorder(root->left, nums, index);
        root->val = nums[index++];
        setValueInorder(root->right, nums, index);
    }
};
```

- [参照](https://github.com/kazukiii/leetcode/pull/25/changes/0f5349d5c358c4e31df7c0d10fd03a926d03d729)
- Inorder traversal とは？：左・根っこ・右の順で見る。
  - c.f., preorder (根、左、右)・postorder（左、右、根）
  - この文脈で使うと値が昇順になる。

# Step 3

OK。
