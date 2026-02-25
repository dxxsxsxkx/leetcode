# 122. Best Time to Buy and Sell Stock II

## Step 1

売買を繰り返せるのが前の問題との違い。機会費用の視点が入る。したがって、買い判断は前の問題と同じで良いが売り判断を変えなきゃいけない。

- 売り判断を forward-looking に行う。ある時点で売った場合に得られる利益と後ろの部分列の中で売買をした時の最大利益とを比較して、大きい方を取る。
- 時間 $O(N^2)$、空間 $O(N)$？時間は $O(N^3)$かも、だめだ

以下のコードにして、36/203。なんかうまくいっていない。

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }

        int min_price = prices[0];
        int max_profit = prices[0] - prices[0];
        std::vector<int> incoming_prices;

        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] < 0) {
                throw std::invalid_argument("Price must not be negative");
            }
            min_price = std::min(min_price, prices[i]);
            incoming_prices = incoming_prices = std::vector<int>(prices.begin() + i, prices.end());
            max_profit = std::max(prices[i] - min_price, _helper(incoming_prices));
        }

        return max_profit;
    }
private: 
    int _helper(std::vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }
        
        int min_price = prices[0];
        int max_profit = prices[0] - prices[0];

        for (auto price : prices) {
            min_price = std::min(min_price, price);
            max_profit = std::max(max_profit, price - min_price);
        }

        return max_profit;
    }
};
```

上がったら売るで良いっぽい。最初はよくわからなかったが、グラフを書いたらちょっと納得が行った。都度都度利確した方が持ち続けるよりもリターンが高くなる。これを `step1.cpp` に書いた。

- 階差の和を最大化するので、正の部分だけを取れば良い。逆に、利益が区間ごとに分解できなくなるとこのアプローチはうまくいかなくなる（例えば、手数料が入る・取引回数に制限がかかる・クールダウン = 売った翌日は inactive などの制約がかかる）
- $i = 1, 2, 3, 4$ の価格を $p_i$ として、$\{1, 4, 2, 6\}$ とする。$i = 1$ で買った株を $i = 2$ で利確して $i = 3$ で買い直すのと $i = 4$ まで持ち越すのとでは下がり分があるため前者の方が利益が大きい。
- 時間計算量 $O(N)$、空間計算量 $O(1)$。

再帰でやる場合、時間と手元に株があるかどうかを引き回す。各時点では売る or そのまま（持っている場合）ないし買う or そのまま（持っていない場合）。都度都度 PL を計上していく。時間 $O(2^N)$ でTLEになった。これにメモを入れると回る。こちらは `recursive_with_memo.cpp` に書いた。

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }
        return _helper(prices, 0, false);
    }
public: 
    int _helper(std::vector<int>& prices, int current_time, bool is_holding) {
        if (current_time == prices.size()) {
            return 0;
        }

        if (is_holding) {  // do nothing or sell
            return std::max(
                _helper(prices, current_time + 1, true), 
                prices[current_time] + _helper(prices, current_time + 1, false)
            );
        } else {  // do nothing or buy
            return std::max(
                _helper(prices, current_time + 1, false),
                -prices[current_time] + _helper(prices, current_time + 1, true)
            );
        }
    }
};
```

## Step 2

色々みてみたが Step 1のやり方が一番シンプルでわかりやすい。

### 勉強

[この書き方](https://github.com/5103246/LeetCode_Arai60/pull/36/changes#diff-e969ee840191df78b19cebeeeaa55e602e2790d373ffd1f7b1c0c96d1a9a98e4R24-R26:~:text=%2B-,%23%23%20Step1,-6)の名付けが良い。

- 買値を持っておくのは違う点ではある。

[参照](https://github.com/olsen-blue/Arai60/pull/38/changes#r1980557395)：状態遷移を入れるとき、行列にするよりも配列を2つ持つ方が良いかも？

- あと自分の書き方だと `-1` がマジックナンバーになってる

## Step 3

同じ方法で3回書いた。
