# Step 1

## 1回目

- 無効なものも含めたペアの総数からペアを引けば良いのではと考えたが、その先が思い浮かばなかった。
- それとは別に、端から順に塗っていく方法もありそうだなと思った。あるフェンスに塗れる色を手元に持っていって、そのうちのどちらかを塗っていき、分岐するごとに総数に1を足していく（木構造っぽくなる？）。

### メモ

- そもそも dynamic programming / 動的計画法という言葉の意味を知らなかった。[Wikipedia](https://en.wikipedia.org/wiki/Dynamic_programming) より：
  > Dynamic programming is both a mathematical optimization method and an algorithmic paradigm ... In both contexts it refers to simplifying a complicated problem by breaking it down into simpler sub-problems in a recursive manner. While some decision problems cannot be taken apart this way, decisions that span several points in time do often break apart recursively. Likewise, in computer science, if a problem can be solved optimally by breaking it into sub-problems and then recursively finding the optimal solutions to the sub-problems, then it is said to have optimal substructure.

## 2回目

フェンスの数を $n$、色の数を $k$ とする。1つ前と2つ前の数を手元に持つ。あるフェンスの塗り方として、1つ前と違う色を塗る場合と1つ前と同じ色を塗る場合の2通りがある。前者であれば1つ前の色一色につき $k - 1$ 通り（これに前ステップでの valid な塗り方を掛ける）。後者であれば2つ前のステップでの valid な塗り方一つにつき $k - 1$ 通り。
  - [参考(Step 2)](https://github.com/Ryotaro25/leetcode_first60/pull/33/changes/b94eecb2f8ad9924c5afaf47f3e7d669e28565a1#diff-c0a97f44bef52da35673570647e42258e3e54bb429cc46df795d7c715164bac6)

### コード

`step1.cpp` に書いた。

# Step 2

メモ化した top-down アプローチのコードを `step2.cpp` に書いた。

## 勉強

Dynamic programming には top-down と bottom-up のアプローチがあり、自分が今回採った方法は後者に当たる。

- 前者は要素を切り分けて範囲を狭めながら再帰で処理していく、後者では $i = 0, 1, \dots$ と昇順に処理していく。
- 前者でやるのであれば、1つ前と同じ色を塗る場合と違う色を塗る場合とを関数の再帰呼び出しで計算する。

[メモ化](https://github.com/Yoshiki-Iwasa/Arai60/pull/44/changes/3a55cc495ac31c94e38e1b39f40055ed9d261f18)？

- Top-down でやると同じ要素を何度も計算することになるので時間計算量が爆発する。これを避けるために配列や hash map を用意しておいて、そこにメモしておくようにする。

[フィボナッチ](https://github.com/goto-untrapped/Arai60/pull/44/changes/b0b76df73f7b0b3c15b5ae4aef0066cfe611eb1b#r1703072395)？

- 漸化式 $dp[n] = (k-1)dp[n-1] + (k-1)dp[n-2]$ なので行列が $M =
\begin{pmatrix}
k-1 & k-1 \\
1 & 0
\end{pmatrix}$ になる。イマイチわかっていないのであとで戻ってくる。

# Step 3

`step3.cpp` に `step1.cpp` と同様の方針で書いた。
