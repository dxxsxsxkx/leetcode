## Step 1

### 1回目

現在の最長長さ・今見ている列の長さ・前の数字の3つの要素を引き回す、現在の数字が前の数字よりも大きかったら今見ている列の長さに1を足す。そうでなければ現在の最長長さと列の長さを比較・更新した上で列の長さをリセットする。

#### コード

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int current_longest_length = 1;
        int current_length = 1;
        int previous_num = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > previous_num) {
                current_length++;
            } else {
                if (current_length > current_longest_length) {
                    current_longest_length = current_length;
                }
                current_length = 1;
            }

            previous_num = nums[i];
        }

        return current_longest_length;
    }
};
```

#### メモ

- 勘違いしていて、間に挟まっている要素を消しても良い。つまり列は中断してもよい。

### 2回目

各要素の時点での最大値をメモしていく。

- 1回目のやり方では一個前の時点での最大値しか引き回していなかったので、ジャンプがある場合に対応できなかった。

#### コード

`step1.cpp` に書いた。

#### メモ

各要素につき前の要素全部と大小比較をしているので冗長な気がする。

## Step 2

### 勉強

[二分探索](https://github.com/Ryotaro25/leetcode_first60/pull/34/changes/61f67b4eb73bee7944a181b8f29a08c94bd3ca38#diff-c7f13211001a462de96bc425c2e9118cd12d731f88eafbc121b3f4ba58d03f47)。

- 最長の increasing subsequence の index を持つ increasing sequence を作る。
  - 命名が悩ましいが、[ここ](https://github.com/mamo3gr/arai60/pull/29/changes#diff-99ef9dfc883fb81ff2f1ba8126bf45e8b41cf737c5540cd1ce53afd3e1e18049)で言及されている `min_tails` は良さそう。各長さの部分列の中で末尾が最小のものを保存しているので。
- `nums` の各要素につき、`std::lower_bound` でこのベクトルと比較する。大きな数が見つかったらベクトルの後ろに足す。
  - [`std::lower_bound`](https://en.cppreference.com/w/cpp/algorithm/lower_bound.html)。`first`, `last` の区間の中で、`value` より前に並ばない最後の（？）要素を返す。

[Binary indexed tree と セグメントツリー](https://github.com/TORUS0818/leetcode/pull/33/changes/1ad295b6777d0321c2ad56bae8e4f8c600459a39)。

- Step 1で感じた↓への対応になっている。$O(n^2)$ を $O(n\log n)$ にする。
  > 各要素につき前の要素全部と大小比較をしているので冗長な気がする。

- 詳しくは後で戻ってくる。

## Step 3

Step 1 の bottom-up dp を書いた（`step3.cpp`）。
