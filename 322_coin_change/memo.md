# 322. Coin Change

## Step 1

合計額を大きいコインから順番に使って埋めていくアプローチを考えた。

- DP table を作って、それぞれのコインを使った回数を記録する。
- 大きい金額のコインから優先的に使っていきたいところだが、コインの金額がソートされていない。`std::set` を使って降順にソートされたリストにするか。
- うまくいかなさそう。例えば `coins = [1, 3, 4], amount = 6` だと厳しい。ここで答えを見る。

Bottom-up dp で解ける。`amount` を埋める最小のコイン数を求める問題は、より小さい合計値を埋めるコイン数を求めるという部分問題の集合として考えられる。`step1.cpp` に書いた。

- コインの枚数を $N$、合計額を $M$ として、時間計算量 $O(N \times M)$、空間計算量 $O(M)$。

## Step 2

Step 1 を修正したものを `step2.cpp` に書いた。

### 勉強

[参照](https://github.com/potrue/leetcode/pull/40/changes#r2264799064)：`NOT_FOUND` に何を入れるかは意見が分かれている。

- めちゃくちゃ大きい値を入れておく派の人がいる。
- [オーバーフロー回避](https://github.com/5103246/LeetCode_Arai60/pull/38/changes#r2658821437)？

[参照](https://github.com/potrue/leetcode/pull/40/changes#r2264798356)：`i` は確かにわかりづらい。

[参照](https://github.com/seal-azarashi/leetcode/pull/37/changes#r1830469401)：BFS / DFS による実装。

- グラフ探索のイメージになる。ノードを現在の `sum`、エッジをコインの金額（ないしはその加算）とみなすと、`amount` というノードまでの最短距離を求める問題として見ることができる。
- DFSは `dfs.cpp` に書いた。
  - 最初 `std::set` を使って書こうとしたが `amount` が大きすぎるケースの枝刈りに失敗したので、`sorted_coins` を作るタイミングで値の判定を入れることにした。
  - 最短距離の問題なので無駄に掘ってしまうのはよくない。
- BFSは `bfs.cpp` に書いた。
  - 
  - Queue を使う / 使わない、使う場合には何を入れておくか、アプローチは色々あるっぽい。あとは引き算でやるとか。

## Step 3

Bottom-up dp を `step3.cpp` に書いた。メモの名付けがわかりづらい気がしたので `fewest_coins` とした。あと BFS を練習して、わかりづらいところを変えたものを `bfs_revised.cpp` に書いた。
