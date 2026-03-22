# 78. Subsets

## Step 1

異なる要素を持つ `nums` について、その部分集合を重複しないように全て返す。

- 制約：`1 <= nums.length <= 10, -10 <= nums[i] <= 10`、配列要素は全て異なる

とりあえず逐次的に構築していこう。最初の要素を決めて、残りの要素について再帰的に `subsets()` を呼び出す。

- 空配列は別途追加しよう。
- 全ての要素について入れる / 入れないの2択があるイメージがある。
- とりあえず書いてみたところ、重複する組み合わせが大量に入ってしまった（コードは以下）。組み合わせの問題を順列のロジックで書いてしまっている感じ（最初に `nums[0]` と `nums[1]` のどちらを入れる判断をしようがこの問題においては変わりはない）。
- するとループがいらないな。これで `step1.cpp` に書いた。ここまで15分。

  ```cpp
  #include <vector>
  class Solution {
  public:
      std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
          if (nums.size() == 0) {
              return {{}};
          }

          std::vector<std::vector<int>> subset;

          for (int i = 0; i < nums.size(); ++i) {
              int first = nums[i];

              std::vector<int> remaining = nums;
              remaining.erase(remaining.begin() + i);

              auto subset_from_remains = subsets(remaining);

              for (auto s : subset_from_remains) {
                  subset.push_back(s);
                  s.insert(s.begin(), first);
                  subset.push_back(s);
              }
          }
          return subset;
      }
  };
  ```

## Step 2

最初、各要素を入れるか入れないかの二択だなと思ったが、以下のように書けるみたい。ビットマスクというらしい。

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        for (int subset = 0; subset < 1 << nums.size(); ++subset) {
            vector<int> subset_in_vector;
            for (int element = 0; element < nums.size(); ++element) {
                if (subset & (1 << element)) {
                    subset_in_vector.emplace_back(nums[element]);
                }
            }
            result.emplace_back(subset_in_vector);
        }
        return result;
    }
};
```

- ビット演算に不慣れで理解に時間がかかった。
  - `subset = 5, element = 2` を例として考えると、`subset = 101, 1 << element = 100` になり、`&` 演算子で `100` となる。0ではないので `true` が返る。
  - このようにして、各パターンについて対応する `element` のみを `subset_in_vector` に入れてあげる。
- [参照](https://github.com/potrue/leetcode/pull/51/changes)

今まで作った `subset` を拡張していくやり方。割としっくりくるかも。`expand_subset.cpp` に書いた。

- [参照](https://github.com/potrue/leetcode/pull/51/changes#diff-3136ed3bcfc720cf03f95de4925ddf5d4c527f5da04a2c855bc0a5598f16a838R11-R35)

バックトラッキング。以下のイメージはわかりやすい
> バックトラックは、要するに、その場所までが固定されたときに、残りをどうやって重複や漏れがないように、分類するかということです。この方法だと、「それ以上ない場合」「次にはじめて含まれるのが i である場合」に分類されていますね。

- `backtracking.cpp` に書いた。このコードであれば、すでに作成ずみの subsets を `subsets_already_made` で管理している。残りの管理の仕方も上のコメントがついているコードと同じかな。「それ以上がない場合」は for loop が回らずにバックトラックされ、「次に初めて含まれるのが `i` である場合」は for loop に入る。
- 樹形図を描いたら dfs だなあと思った。なるほどね。
- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/55/changes#diff-8d24ab5b9b8fee654985b8879549eff71a5fcb3439ce79c22b8ffcc2d4ca2d43)

そうなの？
> 全ての再帰関数は、同じロジックを用いたまま、ループで書き直すことができます。

- 考えてみると、`step1.cpp` を展開したものが `expand_subset.cpp` になっているのか。
- 以後他のものについても考えてみるか。
- [参照](https://github.com/nittoco/leetcode/pull/19/changes#r1644763510)

## Step 3

どれが一番しっくりくるだろう。バックトラックかループで拡張するやつかなあ。
