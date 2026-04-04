# 31. Next Permutation

## Step 1

辞書順で `nums` の次にくる順列を返す。

- 制約：`1 <= nums.length <= 100, 0 <= nums[i] <= 100`
- In-place でやらなければいけない。

15分くらい考えて全くわからなかったので、答えを見る。

- 山（i.e., `nums[i] < nums[i + 1]` となるような最小の `i`）を探す。見つからなければ全体が降順になっているので反転する。見つかったら `nums[i]` よりも大きい要素のうち最小のものを右側から探し、それと入れ替える。その上で右側を昇順にする。
  - 順列を整数値だと考える。
- `std::reverse(first, last)`: `[first, last)` の要素を反転する。
  - [レファレンス](https://en.cppreference.com/w/cpp/algorithm/reverse.html)

## Step 2

`is_sorted_until()`、`rbegin / rend`, `iter_swap()` を使う。`step2.cpp` に書いた。

- 同じやり方だが、イテレータを操作している（[reverse iterator](https://en.cppreference.com/w/cpp/iterator/reverse_iterator.html) だが）。
  - こちらの方がやってることが直感的にわかるかも。あと range に対して操作をするので、入力が vector である必要がないのもいい。これまでいまいちイテレータを使う理由がわかっていなかったんだけど、こういう感覚なのかな？
- まず reverse iterator で後ろから見た時にどこまでがソートされているかを確かめる（step1と同じ）。イテレータが左端でなければ、`*it` よりも大きい最初の要素を `upper_bound()` で見つける。イテレータなので `iter_swap` する。
  - 毎回思うが、`lower_bound / upper_bound` の名前にまだしっくりきてない。
- [参照](https://github.com/potrue/leetcode/pull/58/changes#diff-b91da27b3af89f1d0fe5cb63d51484cc250b67bf72ae803d8607d53abbc4caadR4-R11)
- レファレンス：[`rbegin`](https://en.cppreference.com/w/cpp/iterator/rbegin.html), [`is_sorted_until()`](https://en.cppreference.com/w/cpp/algorithm/is_sorted_until.html)

`next_permutation` あるのか... Possible implementation として載っているのはまさに上のやり方だった：

```cpp
template<class BidirIt>
bool next_permutation(BidirIt first, BidirIt last)
{
    auto r_first = std::make_reverse_iterator(last);
    auto r_last = std::make_reverse_iterator(first);
    auto left = std::is_sorted_until(r_first, r_last);
 
    if (left != r_last)
    {
        auto right = std::upper_bound(r_first, left, *left);
        std::iter_swap(left, right);
    }
 
    std::reverse(left.base(), last);
    return left != r_last;
}
```

- [レファレンス](https://en.cppreference.com/w/cpp/algorithm/next_permutation.html)

アイデアとしては変えずに、二重ループにする方法。まあ、step1と同じくらいかな。

```cpp
#include <algorithm>
#include <vector>
class Solution {
public:
    void nextPermutation(std::vector<int>& nums) {
        for (int i = nums.size() - 2; i >= 0; --i) {
            for (int j = nums.size() - 1; j > i; --j) {
                if (nums[i] >= nums[j]) {
                    continue;
                }

                std::swap(nums[i], nums[j]);

                std::reverse(nums.begin() + i + 1, nums.end());

                return;
            }
        }
        std::reverse(nums.begin(), nums.end());
    }
};
```

- [参照](https://github.com/Mike0121/LeetCode/pull/15/changes)

## Step 3

色々な人の解答を読んだが、考え方の幅はそれほどなくて、その表現の幅も他の問題に比べて小さかった。強いて言えば、C++ だと便利な関数やメソッドが既に定義されているなあというくらい。

`step2.cpp` と同じやり方で `step3.cpp` もかいた。
