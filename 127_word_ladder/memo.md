# Step 1

## 1回目

一文字ずつのスロットを変えていって、なるべくはやく `endword` に近づける。BFS を使う気がする。

- `endword` に毎回近づけようとすると、単語が一つも存在しないことがありうる。先に進んでから戻らなければいけないので非効率。

あらかじめ `wordList` から隣接する単語のリストを作成しておく。`beginword` から順に、隣接する単語を調べる。調べた単語は記録する。既に調べた単語に当たったり、隣接する単語がなくなった場合はそこで止める。`endword` に当たったらそこで返す。

- 隣接する単語のリストを作成するところで詰まって、答えを見た。

## 2回目

隣接する単語のリストを作る・単語を順番に確認していく・確認した単語を記録するという3つのタスクがある。

- 隣接する単語のリストを作成する際には判定とリスト化を切り分けるとわかりやすそう。

- 単語を順番に確認する際には `queue` を使う。

  - [参照](https://cpprefjp.github.io/reference/queue/queue.html)。`stack` と違い、最初に入った要素が最初に出ていく First-in-first-out になっている。

### コード

`step1.cpp` に記載。書くのに10分くらいかかった。

### メモ

単語リストの作成。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/22/commits/7114054de087070fc537f6a53a726672f9a5fdcf)。

`emplace_back()`。

- [参照](https://cpprefjp.github.io/reference/vector/vector.html)。
この問題ではベクトル型のオブジェクトに対して `emplace()` で要素を追加しようとするとうまくいかなかったが、`emplace_back()` に変えたらうまく行った。`emplace()` では要素を構築する位置を指定する必要がある。前の問題では `stack` に対しては `emplace` を、`vector` に対しては `push_back` を使っていた。

`areDifferentByOneWord` を見ながら、二つの単語の長さが違った場合に `false` を返すようにした方が良いなと思った。

## 3回目

8分くらいで書けたので、とりあえず次へ。

# Step 2

色々修正したらかなり速くなった。

## 勉強

インデックスで持つようにする。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/22/commits/f19fe88adc4467f9ff9b531a41f83f071d50710b#r1692669984)。コピーの手間が減らせる。

`WordToLevel` → `WordAndLevel`とする。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/22/commits/f19fe88adc4467f9ff9b531a41f83f071d50710b#r1692661385)。

- 構造体を含むタイプの命名は UpperCamelCase を用いる。[参照](https://google.github.io/styleguide/cppguide.html#Type_Names)。

返り値の `map` と RVO。

- [参照1](https://github.com/Ryotaro25/leetcode_first60/pull/22/commits/7114054de087070fc537f6a53a726672f9a5fdcf#r1686407901)、[参照2](https://github.com/Ryotaro25/leetcode_first60/pull/22/commits/f19fe88adc4467f9ff9b531a41f83f071d50710b#r1692657582)

- この場合であれば、`void makeAdjacencyList(const std::vector<std::string>>& word_list, std::vector<std::vector<std::int>>& idx_adjacent_words)` と定義して、次のように呼び出す。関数内部で値を書き換える。
```cpp
std::vector<std::vector<int>> idx_adjacent_words(wordList.size());
MakeAdjacencyList(word_list, idx_adjacent_words);
```

関数の名前。

- `lowerCamelCase` か `UpperCamelCase` かで混乱がある。とりあえず自分の中では `lowerCamelCase` を使うことにしておく。

文字列のコピーをさらに減らす。

- [string_view](https://github.com/kazukiii/leetcode/pull/21/commits/220114353adbd516188f38e24b2f56c476574648#r1657298258)。[ドキュメント](https://en.cppreference.com/w/cpp/string/basic_string_view.html)。
> The class template basic_string_view describes an object that can refer to a constant contiguous sequence of CharT with the first element of the sequence at position zero.

  - `string_view` タイプのオブジェクトは文字列を指すポインタと文字列のサイズのみをメンバとしてもつ。いちいちコピーしたりしない。文字列比較のところで使うと速くなりそう。

  - 実際使ってみると3倍くらい速くなった...（1411ms → 495ms）。コピーがいかに時間を食うかを実感。

その他細々とした点について。

- [ダイクストラ法による回答](https://github.com/kazukiii/leetcode/pull/21/commits/220114353adbd516188f38e24b2f56c476574648#diff-cbe4ed76c40333f1408fb945ad8635c86d7edbd988d9ded772db4d6ead97ac7a)。今度ちゃんと追う。

  - [ここ](https://discord.com/channels/1084280443945353267/1183683738635346001/1199046289686548581)を見る限り、グラフ上で行うダイクストラ法のうちの特殊ケースがBFSになっているのか？

- [ハミング距離](https://github.com/fhiyo/leetcode/pull/22/commits/7620a3760db59ac7fef843acc00bafc4b8ba06e2)。自分がやっているのはハミング距離を計算した上で1になっているかを確認するというもの。

  - [これ](https://discord.com/channels/1084280443945353267/1200089668901937312/1216123084889788486)も参照した。例えば "abcdefg" と "abXdefg" であれば、先頭から2文字、後ろから4文字が一致している。これを全体の文字数から引くと距離が出る。

# Step 3

書いた。
