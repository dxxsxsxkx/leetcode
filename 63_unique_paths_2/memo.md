## Step 1

### 1回目

組み合わせだと障害物を考慮するのが面倒くさそう。各セルへの unique paths の数を input とする 2D table を作って埋めていく方はシンプルに実装できそう。

- Table のセルを一つ一つ見ていく。セルに障害物があったら table の対応するセルには 0 を入れて `continue` する。そうでなければ62. と同様にやる。

- 時間計算量 $O(m*n)$、空間計算量 $O(m*n)$

- 使ったコードは `step1.cpp` に書いたもの。10分ほどでアクセプトされた。

#### メモ

- 障害物のマーカーがマジックナンバーかも？ `int obstacle_exists = 1` とするとわかりやすいかも。

- 実行時間の見積もり：$0 < m, n < 100$ 、またループは 10 - 20回の操作を含むので、最悪で $100 * 100 * 15 / 10^8 \approx 0.001 sec$位と見積もった。

## Step 2

`step1.cpp` に軽く修正して `step2.cpp` を書いた。

### 勉強

2D table について、スタート地点に障害物がないかどうかを確かめるべき。

- [参照](https://github.com/5103246/LeetCode_Arai60/pull/32/changes/d9f46295cab3d7cd2680897f82ebec9921a6927c#:~:text=%E3%82%B9%E3%82%BF%E3%83%BC%E3%83%88%E5%9C%B0%E7%82%B9%E3%81%AB%E9%9A%9C%E5%AE%B3%E7%89%A9%E3%81%8C%E3%81%82%E3%82%8B%E3%82%B1%E3%83%BC%E3%82%B9%E3%82%92%E8%80%83%E3%81%88%E3%82%8B%E3%81%A8%E3%80%81DP%5B0%5D%5B0%5D%E3%81%AE%E5%88%9D%E6%9C%9F%E5%8C%96%E3%82%82%E9%9A%9C%E5%AE%B3%E7%89%A9%E3%81%8C%E3%81%82%E3%82%8B%E3%81%8B%E7%A2%BA%E8%AA%8D%E3%81%97%E3%81%9F%E3%81%BB%E3%81%86%E3%81%8C%E3%82%88%E3%81%84)

行列の掛け算で解く方法。障害物がない行については要素1の上三角行列をかけることで table を埋められる。

- [参照](https://github.com/5103246/LeetCode_Arai60/pull/32/changes/d9f46295cab3d7cd2680897f82ebec9921a6927c#r2510149243)
- ある行から次の行に進む時の動作が線形変換になっている。
- どういうこっちゃ。
  > N × N の行列の掛け算は O(N^3) で求められるので、 M 乗は Exponentiation by Squaring で O(N^3 log M) で求めることができます。
  - Exponentiation by squaring: 例えば $x^8$ の計算を $x^8 = xxxxxxxx$（$O(N^3)$）ではなく $x^8 = ((x^2)^2)^2$ としてあげると $O(\log N)$ になる。

1D table の場合を `one_dimensional.cpp` に書いた。

例外処理。そもそもベクトルが blank の場合への対処と、ある行すべてに障害物があった場合に打ち切り処理を入れる方法。

- [参照](https://github.com/irohafternoon/LeetCode/pull/37/files)。
- 後者のケースってあんまり思いつかない。この処理を入れることによる計算の効率化の幅と、可読性の低下幅と、どっちが大きいだろう？都度判定を入れることになるので計算の効率化もそこまでされないのではと思う。

障害物の名付けはもっと単純でいいかも。`kObstacle` とか `Obstacle` とか。C++ だと前者？あと `static constexpr` をつけて private におく。

- [参照](https://github.com/olsen-blue/Arai60/pull/34/changes#:~:text=%2D%20%E3%81%BB%E3%81%BC%E5%90%8C%E3%81%98%E3%82%B3%E3%83%BC%E3%83%89%E3%82%92%E8%A6%8B%E3%81%A4%E3%81%91%E3%81%9F%E3%80%82%E3%82%84%E3%81%A3%E3%81%B1%E3%80%8COBSTACLE%20%3D%201%E3%80%8D%E3%81%8C%E8%89%AF%E3%81%84%E3%81%A7%E3%81%99%E3%82%88%E3%81%AD%E3%80%82)

ゼロ代入いるかどうか。table の意味としてはあったほうがわかりやすいと思うが...。

- [参照](https://github.com/olsen-blue/Arai60/pull/34/changes#r1967187228)

## Step 3

`step3.cpp` に書いた。
