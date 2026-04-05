# 8. String to Integer (atoi)

## Step 1

文字列を32ビットの符号付き整数に変換する関数を実装する。

- アルゴリズムの仕組み：
  1. Leading whitespace を無視する
  2. 符号を確認する。符号がなければ正の数とする。
  3. Leading zeros を無視しつつ、non-digit character ないし最後の文字に至るまで数字を読み進める。最後の文字まで進んだら結果を0とする。
  4. `[-2^31, 2^31 - 1]` の範囲に収まらない数字を丸める。
- 制約：`0 <= s.length <= 200`, `s` にはアルファベットと0-9 の数字、スペース、`+, -, .` が含まれる

1文字ずつ左から舐める。スペースを無視する・符号を決める。

- 数字を作るのはどうすれば？ここで詰まってしまったので、答えを見る。

`step1.cpp` に書いた。

- 前に処理した文字 / 数字を左に寄せていく。
- [`isdigit()`](https://en.cppreference.com/w/cpp/string/byte/isdigit.html)を使って判定する。
  - 判定した数字は ASCIIコードでの引き算で整数値にする。
- 数字を作る前に毎回オーバーフローしていないかを確かめる。1. 桁を左にずらしても最大値を超えないか、2. 前の値が最大値を10で割った値とイコールになっている場合、最後の一桁で最大値を超えないか、と言う2つを確かめている。
  - 2の方では除算が切り捨てであることを利用している。
  - なんか、もっといいやり方がありそう

## Step 2

[レファレンス](https://en.cppreference.com/w/cpp/string/byte/atoi.html)の実装例を見てみる。概ね同じ感じだ。

- [`isspace()`](https://en.cppreference.com/w/c/string/byte/isspace.html)
- オーバーフローを見ていない。

`long long` で逃げるやり方もある。

- [参照](https://github.com/potrue/leetcode/pull/59/changes)
- 32ビットの符号付き整数に変換する、ということで `int` ではなく `int32_t` を使っていたが、本当に必要なのか？
  - `int` は少なくとも16ビット以上であることが保証されているが、環境によって具体的な長さが変動する。それに対し `int32_t` は32ビットであることが保証されている。ここの環境依存の可能性を踏まえることがどれくらい大事なのか。
  - [Fixed width integer types](https://en.cppreference.com/w/cpp/types/integer.html)
- そうなんだ（[参照](https://github.com/hayashi-ay/leetcode/pull/69/changes)）。
  > Pythonのintは理論上は上限がないので途中のオーバーフローなどは考えなくて良い。

  - あとは、[この辺](https://github.com/Satorien/LeetCode/pull/58/changes#r2698302800)も。
    > 他の(オーバーフローが)問題になるような言語だと、標準ライブラリーにそういう関数があることが多いというのも意識してもいいかもしれません。
    > まあ、要は自分で作らないべきものであるということです。

7 はわかりづらいので、`numeric_limits::max() % 10` にしておく。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/64/changes#r2014568934)

`isdigit()` のレファレンスに「判定はロケールの影響を受ける」とあったが、こういう例があるのか
> 漢字などでも True になるのは Python の isdigit の話ですね。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/64/changes#r2022734944)

この点は Step 1 のコードを書いた時に思った。
> 符号処理は数値の構築とは分離して最後にするのでも良いのではと思ったが、値の正負によって丸めの閾値が違うので、数値を構築するときに符号処理も同時並行でやった方が良さそうかもしれないと感じた。

- [参照](https://github.com/olsen-blue/Arai60/pull/60/changes)

関数に切り出している解答もいくつかみたが、上から書いた方がわかりやすいと思った。

## Step 3

3回かけるまで練習。前に作った `s_unsigned` をチェックするところの順序が頭から抜けてミスした。
