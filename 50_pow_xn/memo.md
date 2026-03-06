# 50. Pow(x, n)

## Step 1

地道に1ステップずつやる方法を考える。現在の値とステップ数を管理して、ステップ数のカウンターが `n` になったら break して値を返す。`n` の符号に応じて掛ける / 割るのどちらを使うかを分岐させる。エッジケースは `x == 0` と `n == 0` で良いだろう。10分ほどかけて以下のコードを書き、TLE。

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        if (x == 0) {
            return 0;
        }
        if (n == 0) {
            return 1;
        }

        int counter = 0;
        double pow_x_i = 1;

        if (n > 0) {
            for (int i = 1; i <= n; ++i) {
                pow_x_i = pow_x_i * x;
                ++counter;
                if (counter == n) {
                    break;
                }
            }
        } else {
            for (int i = -1; i >= n; --i) {
                pow_x_i = pow_x_i / x; 
                --counter;
                if (counter == n) {
                    break;
                }
            }
        }
        return pow_x_i;
    }
};
```

- 時間計算量は $O(N)$、空間計算量は $O(1)$。
  - $O(|N|)$か。
- 時間の見積もり：1ステップは演算・代入・カウンターの更新・判定で10回くらい。`-2^31 <= n <= 2^31 - 1` なので、最悪の場合だと大体 $10 * 2^{31} / 10^9 = 10$sくらいかかってしまう。TLEは妥当。

（TLEになること以外の）よくない点を考える。

- カウンターいらない
  - なんか、カウンター省くと signed integer overflow になるが、あるとならない。謎。→ `i` を下限で decrement した時に超えるのか、理解。
- `i` を `int64_t` にしとくとよい。
- $0^{-1}$ の処理？

計算量を減らすにはどうする？

- 複数ステップを一気に回せると良い。2ステップずつ / 3ステップずつというのを考えたが、どこまで一気にやれるかということを考えると半分まではいけそう。
- Binary exponentiation。たとえば $x^10 = x^{2^3} * x^{2}$ のように処理する。これで `step1.cpp` に書いた。
  - この指数の扱い方、前に解いた問題のどこかで出てきたな。
  - 時間計算量は $O(\log |N|)$、空間計算量は $O(1)$。

Binary exponentiaion、直感的にパッとわからなかったのでちゃんと書いてみた。$n = 13$ としよう。 1, 0, 1, 1 と binary で右から書いたのと同じになる。

$$
\begin{aligned}
13 &= 1 + 2*6 \\
6 &= 0 + 2*3 \\
3 &= 1 + 2*1 \\
1 &= 1 + 0
\end{aligned}
$$

- $13 = 1 + 2 (0 + 2 (1 + 2))$ と書いてあげると binary になっていることがわかる。ここまで書いてようやく納得が行った。

## Step 2

浮動小数点数は 1.0 のように表記するのが一般的？かも。

- [参照](https://github.com/potrue/leetcode/pull/45/changes#r2272634418)

直接関係はないが、`_` で始まる関数はC++では予約済み。

- [参照](https://github.com/potrue/leetcode/pull/45/changes#r2273215243)
- 前に `_helper()` を private で書いたところにコメントをもらっていた。

割り算の命令って遅いのか...。`n >>= 1` とすると良いらしい。
> 整数の割り算は遅い、ビット演算は速い、という感覚は持っておいたほうが良いと思います。

- [参照1](https://github.com/potrue/leetcode/pull/45/changes#r2272676005)、[参照2](https://github.com/Ryotaro25/leetcode_first60/pull/76#discussion_r2264637640)
- `>>=`：ビットシフトの演算子。指定ビットだけ右に動かす。左であれば `<<=`。知らなかった。
  - [参照](https://stackoverflow.com/questions/38922606/what-is-x-1-and-x-1)

絶対値色々。型に応じて用意されているのか。

- [参照](https://learn.microsoft.com/ja-jp/cpp/c-runtime-library/reference/abs-labs-llabs-abs64?view=msvc-170)。
- 自分の場合だったら `long_abs_n` を作る時は `_abs64()` を使ったほうが良いんだろうか？

へー。
> nが負の場合、毎回割り算をするよりも最後に一発だけやったほうが精度が高くでるのでそうする
- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/48/changes#r1881152340)、`float` と `double` の実装は見ておこう。

この `n < 0` の扱い方は考えたが、どっちの方がいいんだろう...。あとで割る方針だと、負の数をどうするのかが最後までわからないので気持ち悪いと思う人がいるかもしれない。最初にコメントでもつけておく？
> よくよく考えたところ、
> ```python
>   if n < 0:
>     n = -n
>     x = 1.0 / x
> ```
> でよいような気がしてきました。

- [参照](https://github.com/hayashi-ay/leetcode/pull/41/changes#r1514489206)

## Step 3

3回書いた。
