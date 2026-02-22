# 121. Best Time to Buy and Sell Stock

## Step 1

3通り（大きく分けて2種類）考えた。1種類目は全探索型で、それぞれの要素 $i$ について $j < i$ ないし $j > i$ との差を全てとっていくやり方。もう一つは分割統治。

- `prices.length < 10^5` なので $O(N^2)$ の全探索はきついだろうからパス。
- 分割統治：割って左側だけ、右側だけ、クロスの最大値を計算し最も大きいものを返していく。時間計算量 $O(N \log N)$、空間計算量 $O(\log N)$。`step1.cpp` はこれで書いた。
  - もっと早いやり方があるっぽいが。

一応全探索も書いてみたが、予想通り長い配列の場合で TLE。

```cpp
#include <vector>
class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        if (prices.size() == 1) {
            return 0;
        }

        int max_return = 0;

        for (int i = 0; i < prices.size(); i++) {
            int max_diff_i = 0;
            for (int j = i + 1; j < prices.size(); j++) {
                max_diff_i = std::max(max_diff_i, prices[j] - prices[i]); 
            }
            max_return = std::max(max_return, max_diff_i);
        }

        return max_return;
    }
};
```

## Step 2

### 勉強

`cross_max_return = max_right - min_left` とした方がわかりやすそうだと思った。

[参照](https://github.com/5103246/LeetCode_Arai60/pull/35/changes#:~:text=%2B-,%2D%20%E6%9C%80%E5%B0%8F%E4%BE%A1%E6%A0%BC%E3%82%92%E6%9B%B4%E6%96%B0%E3%81%97%E3%81%A6%E3%81%84%E3%81%8F%E6%96%B9%E6%B3%95,-11)：最小価格と最大利益（最大価格　- 最小価格）を持てばもっと単純にできるじゃん...。これで `step2.cpp` に書いた。

- 初期値はそれぞれ `prices[0]` と `0` （`prices[0] - prices[0]`）とする。順番に新しい価格を見ていってそれぞれの要素を更新する。最後に最大利益が0を下回ったら 0 を返す（実際的には  `std::max()` で良い）。
- 時間計算量は $O(N)$、空間計算量は $O(1)$ になる。
- よく考えたら `prices.empty()` の場合を別に処理したほうが良いか → 後付けで入れた。

[参照](https://github.com/naoto-iwase/leetcode/pull/42/changes#r2478711911)：確かにそうだがどう実装できるのか？

- 今買った場合の価格と今売った場合の利益を持ち続けるということか; 結局は同じっぽい

[参照](https://github.com/irohafternoon/LeetCode/pull/40/changes#:~:text=%2D%20%E8%B2%A0%E3%81%AE%E6%95%B0%E3%81%82%E3%82%8B%E3%81%AA%E3%82%89%E4%BE%8B%E5%A4%96%E3%82%92%E6%8A%95%E3%81%92%E3%82%8B%E3%80%81%E6%9C%80%E5%AE%89%E5%80%A4%E3%81%AE%E6%9B%B4%E6%96%B0%E3%81%8C%E3%81%82%E3%82%8B%E3%81%8B%E3%81%A7%E5%A0%B4%E5%90%88%E5%88%86%E3%81%91%E3%82%92%E3%81%99%E3%82%8B%E6%96%B9%E6%B3%95%E3%81%A7)：負の価格が入っていた時に例外を返すようにするとよさそう

- `throw std::invalid_argument("Price must be positive")`

割とどれも似たようなコードだが、どのような自然言語で表現するかによって落とし込むコードが変わってくる感じがする。右から見ることを空売りと表現する人がいたり。

[参照](https://discord.com/channels/1084280443945353267/1196472827457589338/1196473519689703444)：関数型言語の書き方を真似する話か。

- こんな感じになるみたいだけど読みづらすぎる

  ```cpp
  auto prefix_min = prices
      | std::views::partial_sum([](int a, int b){
          return std::min(a, b);
        });

  auto profit = std::views::zip(prices, prefix_min)
      | std::views::transform([](auto p){
          return std::get<0>(p) - std::get<1>(p);
        });

  int ans = std::ranges::max(profit);
  ```

- 昔 Haskell に興味を持ったことがあったが挫折したのを思い出した、またやってみようかなと思う

## Step 3

Step 2 のやり方で `step3.cpp` を書いた。
