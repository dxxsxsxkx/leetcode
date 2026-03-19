# 209. Minimum Size Subarray Sum

## Step 1

とりあえず sliding window を使ってできないか考えてみる。

幅最小からスタートする。`right` を末尾まで運びつつ、都度都度 `left` を `right` から左に伸ばす。和が`target` を超えたら `min_size` を更新する。

```cpp
#include <limits>
#include <vector>
class Solution {
public:
    int minSubArrayLen(int target, std::vector<int>& nums) {
        int left = 0;
        int min_size = std::numeric_limits<int>::max();

        for (int right = 0; right < nums.size(); ++right) {
            int subarray_sum = 0;

            for (int left = right; left >= 0; --left) {
                subarray_sum += nums[left];

                if (subarray_sum >= target) {
                    min_size = std::min(min_size, right - left + 1);
                    break;
                }
            }
        }

        return (min_size == std::numeric_limits<int>::max()) ? 0 : min_size;
    }
};
```

- ちょっと効率が悪いような気もするが、停止条件もないし minimum を探すのが要件なので仕方ないのかな。
- 時間計算量 $O(n^2)$、空間計算量 $O(1)$。
- と思ったが TLE。`target <= 10^9, nums.length <= 10^5, nums[i] <= 10^4` をみていなかった...

最初ちょっと考えたのは、`target` を超えた瞬間に window を縮めていくというもの。この時は問題の条件をちゃんとみてなくて、`target` と一致しなければいけないと思っていたので WA になった。けど同じやり方は別に `target` を超えても良い場合でもつかえるのでは？

- これで `step1.cpp` に書いて accept。

## Step 2

三項演算子使っている人がいないかも。

部分和を使う方法。前に subarray sum の問題でやったな...。`cumsum.cpp` に書いてみる。なんか、この`cumulative_sum` を累積和と呼ぶのが気持ち悪い感覚があるな。最初の要素があるからだが（厳密厨すぎる）。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/53/changes#diff-6a64c47210ca6f4fcbad0816e81d5e4f4238595d0619e7d939938e1fb7bfcd4a)
- 部分和の計算方法は愚直にやる方法の他に [`partial_sum()` を使う方法](https://github.com/Ryotaro25/leetcode_first60/pull/53/changes#r2202480855)もあった。

二分探索の話が出てきているので、自分も `binary_search.cpp` に書いてみた。累積和のベクトルを作る（単調増加になるのでそれが使える）。`right` を固定して、残りの分を埋められるような最大の `left` を探す。

こんなふうにも書けるか...
> leetcodeの解答例でsum += nums[r++];というふうにインクリメントしながらsumに追加する方法があった。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/53/changes#:~:text=leetcode%E3%81%AE%E8%A7%A3%E7%AD%94%E4%BE%8B%E3%81%A7sum%20%2B%3D%20nums%5Br%2B%2B%5D%3B%E3%81%A8%E3%81%84%E3%81%86%E3%81%B5%E3%81%86%E3%81%AB%E3%82%A4%E3%83%B3%E3%82%AF%E3%83%AA%E3%83%A1%E3%83%B3%E3%83%88%E3%81%97%E3%81%AA%E3%81%8C%E3%82%89sum%E3%81%AB%E8%BF%BD%E5%8A%A0%E3%81%99%E3%82%8B%E6%96%B9%E6%B3%95%E3%81%8C%E3%81%82%E3%81%A3%E3%81%9F%E3%80%82)

`nums` の要素が全部正だから効率化できている側面はある。負だったら最初 TLE になったやつみたいにやるしかないかしら。

`min_size` の定義の仕方に感覚の違いがあるな。

## Step 3

最初のやり方が一番しっくりくる。
