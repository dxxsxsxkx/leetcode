# Step 1

## 1回目

### コード

方針が立たなかった。

## 2回目

### コード

まず、1つ目の配列の各要素と2つ目の配列の最小値のペアを和が小さい順に設定した priority queue に入れる。
次に、priority queue の一番上のペアをとって返り値のベクトルに入れる。
この時、とったペアと1つ目のindexが同じで、2つ目のindexが一つ大きいペアを priority queue に入れる。
これを繰り返す。

- [参考](https://github.com/Hurukawa2121/leetcode/blob/find-k-pairs-with-smallest-sums/3.heap/find-k-pairs-with-smallest-sums/step1.cpp)

```cpp
#include <queue>

class Solution {
public:
  std::vector<std::vector<int>> kSmallestPairs(
    std::vector<int>& nums1, 
    std::vector<int>& nums2, 
    int k) {
      auto compareSum = [&nums1, &nums2](IndexPair& a, IndexPair& b) {
        return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
      };

      std::vector<std::vector<int>> k_smallest_pairs;
      std::priority_queue<IndexPair, std::vector<IndexPair>, decltype(compareSum)> smallest_pairs(compareSum);
      for (int i = 0; i < nums1.size(); ++i) {
          smallest_pairs.emplace(i, 0);
      }
      while (k-- > 0) {
        auto [index1, index2] = smallest_pairs.top();
        smallest_pairs.pop();
        k_smallest_pairs.push_back({nums1[index1], nums2[index2]});
        if (index2 + 1 < nums2.size()) {
          smallest_pairs.emplace(index1, index2 + 1);
        }
      }
      return k_smallest_pairs;
  }

private:
  typedef std::pair<int, int> IndexPair;
};
```

### メモ

わからないことが多いので整理していく。

- インデックスを使って管理する。インデックス間の対応関係が分かりづらくて理解に手間取った。数字の対応関係を意識。

- `typedef 元の型 新しい名前`: エイリアスを作る。読みやすさのための操作。

  - 現代的には `using` を使うとのこと（https://github.com/Hurukawa2121/leetcode/pull/10#discussion_r1885771755）。
  `using IndexPair = std::pair<int, int>;`となる。

- `compareSum` はラムダ関数になっている。`bool operator()(IndexPair& a, IndexPair& b) const;` と同じ。
  ```cpp
  // 基本的な書き方
  [capture](parameters) -> return_type {
      body
  };
  ```

  - `[&nums1, &nums2]`: キャプチャ参照。ラムダ関数の外にある変数を使うために使う。毎回コピーしないように&を使う。
  `[&]` としてまとめて参照キャプチャもできる。変数が多い時とかにはこう書くのも良いかも。

  - `decltype` でこの型そのものを取得している。それとは別に `smallest_pairs(decltype)` で具体的に使うものを宣言する。

  - `const IndexPair& a` というふうに const 参照しておいた方が良いのだろうか？

- lower_lower と lowerUpper, UpperUpper の使い分けはどうするのが良いだろうか。調べてみる。

  - [ここ](https://google.github.io/styleguide/cppguide.html#Naming)には特になし。Reddit とかでも荒れてる。

  - なぜかわからないが `typedef std::pairs<int, int> IndexPair` に限っていえばこっちの方が `... index_pair` よりも見やすい気がする。

- 任意の場所に挿入できる `.insert()` は順序を最初に決めてある priority_queue には当然使えない。

# Step 2

## 勉強

参考1：https://github.com/irohafternoon/LeetCode/pull/12/commits/b8b7d909ddc8c68397ca80c195f4a57f6f6f7676

- struct を作っている。名前は `SumAndIndices` が好みかな。
  ```cpp
  struct PairSumAndIndexes {
    int pair_sum;
    int index1;
    int index2;
    // operaor< for max_heap
    bool operator<(const PairSumAndIndexes& other) const {
        if (pair_sum == other.pair_sum) {
            if (index1 == other.index1){
                return index2 < other.index2;
            }
            return index1 < other.index1;
        }
        return pair_sum < other.pair_sum;
    }
  };
  ```

  - このやり方だと [`<=>` 演算子](https://github.com/irohafternoon/LeetCode/pull/12/commits/b8b7d909ddc8c68397ca80c195f4a57f6f6f7676#r2030041029)を使って単純化できる。
    ```cpp
    auto operator<=>(const PairSumAndIndexes& other) const {
      return pair_sum <=> other.pair_sum;
    }
    ```

参考2：https://github.com/Hurukawa2121/leetcode/pull/10

- `while (k--) {...}` よりも `for (int i = 0; i < k; i++>){...}` の方が親切か？

  - [意見](https://github.com/irohafternoon/LeetCode/pull/12/commits/b8b7d909ddc8c68397ca80c195f4a57f6f6f7676#r2030085706)：
  入力を減らすことへの違和感。

参考3：https://github.com/Ryotaro25/leetcode_first60/pull/11/files

- [pair と tupple](https://github.com/Ryotaro25/leetcode_first60/pull/11/files#r1627666649)。
この場合であれば `IndexPair` としているので index が入っていることは明確なので良いだろう。

その他

- `int count = k;` のようにしてあげても良いか？とはいえ、ところどころに`k`は登場するのでトータルで見れば意味はわかるような。

- [具体的な状況に落とし込む](https://discord.com/channels/1084280443945353267/1183683738635346001/1187304667126976532)。
何か実態のある状況を考えて、それを極端なシナリオにしてみるイメージ。次から解く前にイメージを作っていこうか。
  > 11にしても、10にしても、私は、正直な話、人手でやるときにどうやるかだと思っています。「あなたは部屋に入りました。数字の一つ書かれた紙を1000枚あります。その中から和が5000になる2枚を見つけてください。」というときに、100万回足し算しますかねえ。そうしないんだとしたら、どうやります? で、それをコードに書き換えるとどうなりますか?

  - 具体的な状況に落として操作を考えるのと同時に、前の問題にコメントをもらっていたように計算量の見積りを考えてみるようにするか。

- [空だったら？](https://github.com/Fuminiton/LeetCode/pull/10#discussion_r1967051129)。
Python ではヒープが空だったらエラーが出るみたいだが、C++ では undefined behavior になる (https://stackoverflow.com/questions/7390126/what-should-the-pop-method-return-when-the-stack-is-empty)。ちゃんと書いておいた方が良さそう。

  - 他にも、`nums1`, `nums2`, `k` が空 / 0だったケースに対応しておく。

- double for で書いてみる。
  ```cpp
  #include <vector>
  #include <queue>

  class Solution {
  public:
      std::vector<std::vector<int>> kSmallestPairs(
          std::vector<int>& nums1,
          std::vector<int>& nums2,
          int k) {

          if (nums1.empty() || nums2.empty() || k == 0) {
              return {};
          }

          // (sum, i, j) を入れる max-heap
          std::priority_queue<sum_and_indices> all_pairs;

          for (int i = 0; i < nums1.size(); ++i) {
              for (int j = 0; j < nums2.size(); ++j) {
                  int sum = nums1[i] + nums2[j];

                  if (all_pairs.size() < k) {
                      all_pairs.push({sum, {i, j}});
                  } else if (sum < all_pairs.top().first) {
                      all_pairs.pop();
                      all_pairs.push({sum, {i, j}});
                  } else {
                      break;
                  }
              }
          }

          std::vector<std::vector<int>> k_smallest_pairs;
          while (!all_pairs.empty()) {
              auto [sum, idx] = all_pairs.top();
              all_pairs.pop();
              k_smallest_pairs.push_back({nums1[idx.first], nums2[idx.second]});
          }

          return k_smallest_pairs;
      }
  private: 
      using sum_and_indices = std::pair<int, std::pair<int,int>>;
  };
  ```

  - ようやく「枝刈り」とか「定数倍」とか、色々な言葉のイメージが掴めてきた。

# Step 3

OK。
