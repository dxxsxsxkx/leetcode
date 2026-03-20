# 46. Permutations

## Step 1

`nums` の要素を入れ替えたものを全て返す。

- 制約：`1 <= nums.length <= 6, -10 <= nums[i] <= 10`。重複なし。意外と緩い。

あまりパッと思いつかない。手作業でやるとするとどうなるだろう？`nums = [1, 2, 3]` の場合を考える。先に答えの長さを確定させる。6通りあって、いちばん左にそれぞれの要素が入るものが2つずつある。その2つのそれぞれについて残りの2つの要素の permutations を求める。Recursion っぽさがある？

- 最初に長さを固定する必要はない。完成したら `push_back` していけば良いか。
- 「いちばん左にそれぞれの要素が入るものが2つずつある。その2つのそれぞれについて残りの2つの要素の permutations を求める」これをやってしまうと重複が出てきてしまう。各要素を1つずつ先頭に置いて、残りを再帰で求める、で良い。

ここまでの方針で `step1.cpp` に書いた。30分くらい。

- `nums.size() == 1` のケースに対処していないと、ループに入らずに空の `permutations` が返される。これが上の階層に伝播する。

## Step 2

どういうことだろう。

> resultにpush_backとかemplace_backするとき順列をコピーしてから入れなくて大丈夫なのかと思ったんですが、オブジェクトそのものではなくてコンストラクタの引数として渡されてそれをもとに新しい要素が作られるという挙動なのでいらないみたいです。pythonのlist.appendとは違いますね。

- あー、理解した。

  ```python
  result = []
  v = [1, 2, 3]
  result.append(v)
  v[0] = 10
  ```

- [参照](https://github.com/potrue/leetcode/pull/50/changes)

`std::next_permutation()` を使った方法。`next_permutation(begin, end)` は現在の配列を辞書順で次に大きい並びに変換し、次がなければ `false` を返す（つまり最後の順列に到達した状態）。`next_permutaitons.cpp` に書いた。

- 変換と真偽値を返すのを両方やっているのか。
- めっちゃ速くなった。これは `next_permutation()` の内部動作の問題っぽい。実装例をパッとみる限り右から見て次の入れ替え対象を走査 → swap → 右側を reverse、という3ステップで回っている。
  - [ドキュメント](https://cpprefjp.github.io/reference/algorithm/next_permutation.html)
- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/54/changes#diff-b6beff43bfb35327f60d155338aa78168922d58721dd12c440a77d238aa99885)

いまいち stack を使ったやり方のお気持ちがわかっていない。どういうメリットがあるんだろうか？

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/54/changes#diff-b6beff43bfb35327f60d155338aa78168922d58721dd12c440a77d238aa99885R1-R4)

バックトラック？：「部分解を1つずつ拡張し、条件を満たさない場合は戻って別の選択を試す」ような方法。

- この問題であれば、未使用の要素から1つ選んで並べ、最後まで到達したら（i.e., 長さが `n` に到達したら）1つの順列として確定する、というイメージ。
- [参照](https://github.com/olsen-blue/Arai60/pull/51/changes)
- `backtracking.cpp` に書いた。なんかまだしっくりきていない。
  - `std::swap()` のやっていることと全体のイメージを合わせたらちょっとわかったような...？ある位置に置く要素を決めて、残りを埋めるというのをやっている。この時に `nums` を破壊的に変更してしまうのではなく、あくまでも `permutations` を変更し、`nums` は都度都度元に戻している。
- うーん、わかったんだけど、`step1.cpp` のやり方の方が直感的に感じる。

## Step 3

3回書いた。
