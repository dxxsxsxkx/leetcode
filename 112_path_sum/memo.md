# Step 1

## 1回目

ノードを辿っていって、最後まで到達した時点で `targetSum` と比較する。最後まで到達したかどうかは子が `nullptr` かどうかで判定する。

コードに落とすのができなかった。まだ再帰の書き方がわかっていない。

## 2回目

書けた。手元のノードの値を `targetSum` から引いていく方法にした。

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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return false;
        }

        int remaining = targetSum - root->val;

        if (!root->left && !root->right) {
            if (remaining == 0) {
                return true;
            }
        }

        bool left = hasPathSum(root->left, remaining);
        bool right = hasPathSum(root->right, remaining);

        return left || right;
    }
};
```

### メモ

なんというか、初見では self-containing かつ相似な形に機能を落とし込むのができていないんだと思う。

BFS。こっちは試行錯誤しながら書けた。

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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return false;
        }

        int sum = root->val;
        std::queue<RootAndSum> visiting;
        visiting.emplace(root, sum);

        while (!visiting.empty()) {
            auto [parent, current_sum] = visiting.front();
            visiting.pop();

            if (!parent->left && !parent->right) {
                if (current_sum == targetSum) {
                    return true;
                }
            }

            if (parent->left) {
                int left_sum = current_sum + parent->left->val;
                visiting.emplace(parent->left, left_sum);
                
            }
            if (parent->right) {
                int right_sum = current_sum + parent->right->val;
                visiting.emplace(parent->right, right_sum);
            }
        }
        return false;
    }
private:
    struct RootAndSum{
        TreeNode* root;
        int sum;
    };
};
```

- `if (parent->left) {...}` のところは前にどこかの問題ですっ飛ばしてエラーになっていたので、今回すぐ思い出したのは良かった。

# Step 2

条件に合う葉を見つけた時点で返したいので、BFSでやるメリットはあまりない？

- [参照](https://github.com/kazukiii/leetcode/pull/26/changes/085f1be939a8a129921f05ddebc4e78acb6e3f10#diff-13f9d7b0ed2ebf0beb12f452b8b10dbbc05842a4cbc65def0367397a58246274R1-R2)
- ただ、`stack` を使っても `queue` を使っても速さにもメモリ消費にも差が出なかった。

足し上げにすると、private 関数を一つ書いて、状態を三つ持たせる必要が出てくる（親ノード・現在の和・最終的な和）。

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
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) {
            return false;
        }
        return explorePath(root, 0, targetSum);
    }
private:
    bool explorePath(TreeNode* node, int current_sum, int target_sum) {
        if (!node) {
            return false;
        }

        int new_sum = current_sum + node->val;

        if (!node->left && !node->right) {
            if (new_sum == target_sum) {
                return true;
            }
        }

        bool left = explorePath(node->left, new_sum, target_sum);
        bool right = explorePath(node->right, new_sum, target_sum);
        return left || right;
    }
};
```

# Step 3

問題なく書けた。再帰と BFS / DFS を書いた。
