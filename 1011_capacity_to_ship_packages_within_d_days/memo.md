# 1011. Capacity To Ship Packages Within D Days

## Step 1

うまく解ける形に落とし込めないかを考える。二分探索のセクションということもあり、境界を探す形に落とし込めないか考えてみた。

まず、`weights` の値の合計を `days` で割った商を切り上げることで最小の船のキャパシティが求められると考えた。まず最小キャパシティ（`min_capacity`）で荷物を運べるかを試し、運べなければキャパシティ（`capacity`）を1ずつ増やしていくという方針。

- [モデル化](https://github.com/Ryotaro25/leetcode_first60/pull/47/changes#r1874210398)
- 合計の計算には [`std::accumulate`](https://cpprefjp.github.io/reference/numeric/accumulate.html) を用いる。

こう考えると、`weights` を部分配列へ分割していく問題に見える。左から見て行ったとき、そこまでの和が `capacity` を超えるかどうかで真偽値を配列の要素に与えられる。すると `[false, false, true, true]` のような配列の最初の `true` のインデックスを求める問題として捉えられる。そのような区切りの数が `days - 1` で収まれば良い。

ここまで考えたところで30分くらい経ったのと、そこから先が思い浮かばなかったので答えを見る。

- `min_capacity` の考え方が間違っている。例えば `weights = [10, 1, 1, 1], days = 2` だと最初の荷物が積めなくなってしまう。
- 別のモデル化を考えた方が良い：荷物の配列を所与とし、`capacity` に対応する配列を考えて、それぞれのキャパシティで荷物を運ぶのにかかる最小の日数でその配列を埋めていく。キャパシティが増えるほど日数は（広義単調）減少するので、配列の要素が `days` を下回るかどうかで`[false, false, ..., true, true, true]` という真偽値列と対応させることができる。
  - あー、すごいわかりやすい。

この発想をコードに対応させる。`step1.cpp`に書いた。
- 時間計算量：二分探索の中で毎回 `weights` を舐めるので、`weights` の長さを $N$、合計の重さを `sum` として $O(N \log (sum))$
- 空間計算量：$O(1)$
- 実行時間：`weights.length <= 5 * 10^4`、`1 < weights[i] <= 500` より、ひどい場合は `sum = 1 + (500 * 5 * 10^4 - 1)` か。するとざっくり $25 * 5 * 10^4 / 10^9 \approx 10^{-3}$s。結構短いんだなあ。
  - `days < 5*10^4` はやばすぎる。

## Step 2

`canShip()` の中、重さの判定をするところ。現実だったらどうする？積もうとする → 重量オーバーになったら「残りまた明日やるか」となり出航させる、明日になる、重さ0にリセットという順序か。

- この順序に照らすと、`sum += weight` と `sum = 0` を `sum = weight` として一気にやってしまうのは良くないなあ。
- 強いていうなら `++days_used` と `sum = 0` の順序を変えるくらいかな
- [参照](https://github.com/potrue/leetcode/pull/44/changes#r2270260504)

ラムダを書いている人へのコメント。並列計算の話はラムダの使い所としてどこかでみた気がするがどこだったか忘れてしまった...。
> 数行を超えるラムダ関数は、ネストが深くなったり、ラムダ関数の前後を追う際に目の移動量が多くなったりと、読みにくく感じます。メンバ関数にくくりだしたほうが良いと思います。
> 並列計算フレームワークに渡すロジックを記述する際や、 UI のイベントハンドラーを大量に書かなければならない場合等、ラムダ関数にせざるを得ない場合もあるとは思います。

- [参照](https://github.com/potrue/leetcode/pull/44/changes#r2276124905)

`std::accumulate` の代わりに [`std::reduce`](https://cpprefjp.github.io/reference/numeric/reduce.html)。C++17から。どっちがいいかは正直分からず。

- `reduce` は集計の順番を規定していない。
- [参照](https://github.com/potrue/leetcode/pull/44/changes#r2269966119)

`days_use` の初期化は確かに迷ったなー。ただ実際に運ぶとなると1日目のスタートからやるはずなので1にするのが適切。

- [参照](https://github.com/potrue/leetcode/pull/44/changes#:~:text=%E3%81%A7%E5%88%9D%E6%9C%9F%E5%8C%96-,%E3%81%97,-%E3%81%A6%E3%81%97%E3%81%BE%E3%81%84)

二分探索であることを早めに明示するか。どこかにコメントを1-2行入れておくか、ということで `step2.cpp` では最初に2行書いた。これで伝わるかしら。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/51/changes#r1968588852)

あと `left, right` よりも `min_capacity, max_capacity` とした方が良いかもしれない。

なるほど？うーん。でもキャパシティの配列の要素は考慮できるものだけが入っているから大丈夫なんじゃないか。一応最初のところでコメントを入れておいても良いかも。
> weightsの中にcapacityを超えるweightが一つでもあればfalseになるべきですが、このコードだとtrueになりうりますね
> 実際は、leftの初期値をmax(weights)にしているので耐えていますが、現在この初期値がプラスマイナス1ずれるとバグるので、すこし不安な気持ちになりました

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/51/changes#r1987809727)

## Step 3

3回通して書いた。いい感じ。
