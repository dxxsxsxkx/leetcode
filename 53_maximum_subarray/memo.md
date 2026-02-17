## Step 1

### 1回目

愚直に二重ループでやろうと試みた。$i$ について、$0 < j < i$ となる要素を `nums[i]` に順番に足していって、都度都度評価する。うまくいかず。

- ChatGPTに聞いてみて、メモの0が原因だとわかる。部分配列の和は負になりうるので、初期値を変える必要がある。外側のループの中で `nums[i]` で初期化したらこの部分はうまくいった。
- で、TLEになった。 `nums.length <= 10^5` で$O^2$ なのでやむない。見積もりをできる様にならなければ...

```cpp
#include <limits>
#include <vector>
class Solution {
public:
    int maxSubArray(std::vector<int>& nums) {
        std::vector<int> memo_largest_sums(nums.size(), 0);
        int largest_sum = std::numeric_limits<int>::min();

        for (int i = 0; i < nums.size(); i++) {
            int sum = nums[i];
            for (int j = i; j >= 0; j--) {
                sum = sum + nums[j];
                if (sum > memo_largest_sums[i]) {
                    memo_largest_sums[i] = sum;
                }
            }
            largest_sum = std::max(largest_sum, memo_largest_sums[i]);
        }

        return largest_sum;
    }
};
```

### 2回目

どうも他のやり方が思いつかなかった。他の方は累積和を連想するらしいので、それでやってみることに。

- [参照1](https://github.com/5103246/LeetCode_Arai60/pull/30/changes/a08eb2fb366cee8fe7a865229a2b2fb184f52646#diff-0bb2a784ed14f7b9f9b0b632ec69ad39e239dc06d04e0e1aa45d48ae5a786655)、[参照2](https://github.com/mamo3gr/arai60/pull/30/changes#diff-c0cbe2fd6d52cd3b47dd01eeadaf1bd1ead8275e34e9faed47163982125c6cfb)。

- 現在の累積和からこれまでの最小累積和を引いたものを手元に置いておく。これだと $O(n)$ でいける。

- コードは `step1.cpp` に書いた。

## Step 2

色々みてみたが、結局 Step 1 の累積和が一番直感的。ついで Kadane。

### 勉強

Kadane's algorithm。`step2.cpp` に書いた。

- [参照](https://github.com/fhiyo/leetcode/pull/33/changes)。
- `i` で終わる最大部分配列は `i - 1` の最大部分配列に `i` を足したものか、`i` 単体かのどちらか。前者がマイナスならば必ず後者の方が大きくなるので前者は捨てれば良い。
- [相続の例え](https://github.com/naoto-iwase/leetcode/pull/37)はわかりやすい。負の遺産は放棄した方がいいよね、という。

他にも、Divide-and-conquer approach というのがある。`divide_and_conquer.cpp` に書いた。

- 配列を真ん中で2つに分ける。最大部分和は左側・右側・中央を跨ぐのどれか。
- 中央を跨ぐものは、両側に伸ばしていってそれぞれ最大のものの和をとって求める。

## Step 3

累積和で3回書いた（`step3.cpp`）。
