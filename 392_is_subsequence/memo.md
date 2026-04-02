# 392. Is Subsequence

## Step 1

ある配列が別の配列の subsequence であるかどうかを判定する。

- 制約：`0 <= s.length <= 100, 0 <= t.length <= 10^4`, `s, t` には小文字のアルファベットのみが含まれる。

`s` の要素を一つずつ探していくアプローチを考える。

- 手作業のイメージ：`s.length` 人の作業員を用意して、それぞれに一文字を割り当て、`t` の中を探してもらう。見つかったらその文字のインデックスを報告してもらう。見つからなかったらその時点で作業を終了する。前の人からインデックスを引き継ぎ、その次の文字から探し始めてもらう。
- これで `step1.cpp` に書き、アクセプト。10分ほど。
  - 時間計算量：`t` の長さを $N$ として $O(N)$。
  - 空間計算量：$O(1)$

フォローアップ考える。たくさんの `s` （`t` の長さよりも多い）に対してこの操作をしなければいけない場合どうするか。
> Suppose there are lots of incoming s, say s1, s2, ..., sk where k >= 10^9, and you want to check one by one to see if t has its subsequence. In this scenario, how would you change your code?

- これは一個見つければ良いのか、それとも全部を判定する必要があるのかな？後者であれば一個一個判定していくしかないわけで、前者なのかな。
- どうにかして確かめる数を減らしたい。一案として、`t` の要素の組み合わせを生成してそれに一致するものがあるかを探すとか？
  - これ以上思いつかん。

## Step 2

フォローアップについて。全然思いつかなかったのと、理解するのに時間がかかった。あと、そもそも上に書いた「`t` の要素の組み合わせを作る」のは不可能なのか。全てを判定する感じか。

> tにおいてある文字が出てくるindexの配列を`<char, vector<int>>`の辞書として管理しておいて、現在の場所以降で一番最初にあるs中の文字が出てくる場所を二分探索で探す方法（1つのsあたりの時間計算量O(|s|log|s|)）
> この問題のように文字の種類が固定されている（26種類だけ）の場合は、tにおけるすべてのindexにおいて次にある文字が出てくるindexが書いてある配列を最初に構成してしまうことで、1つのsあたりの計算量をo(|s|)にすることもできる。（ただしその配列の構成にO(|t| × 文字の種類)の時間とメモリがかかるので大体のユースケースで見合ってなさそうな気はする）

- 1つ目の方法：`t = "abcab"` であれば、`a - [0, 3], b - [1, 4], c - [2]`。`s = "ab"` の例を考えると、aは0、bは0より後で最小の index として1を探す。これを二分探索でやることで、sの各文字ごとに $O(\log |t|)$ で調べられる。なるほど〜。
- 2つ目の方法：なにこれ？`t = "abcab"` であれば、`i = 0: a - 0, b - 1, c - 2` みたいにする。こうすると、例えば `s = "ab"` の時であれば 0 → 1 という感じでいける。なるほど。これによってそれぞれの文字ごとに $O(1)$ で遷移していけるようになる。
  - 配列の構成が面倒なのも書いてある通りか。
- [参照](https://github.com/potrue/leetcode/pull/57/changes)。

へー。
> C++の標準規格はドラフト版が無料で公開されているらしいが正式版は有料らしい。
> というか、3年おきの更新だったのか。これも知らなかった。

- [参照](https://github.com/potrue/leetcode/pull/57/changes)

他のコードを見る。Step 1 のコードが冗長に見える。

- わざわざ `findChr` を切り分けたところかな。これは必要なのかしら。
  - [これ](https://github.com/olsen-blue/Arai60/pull/58/changes)の最初のコードは、もっと短く済んでいる。こうなるかな：

  ```cpp
  class Solution {
  public:
      bool isSubsequence(std::string s, std::string t) {
          if (s.size() == 0) {
              return true;
          }
          if (t.size() == 0) {
              return false;
          }

          int s_index = 0;
          for (const auto& ch : t) {
              if (s[s_index] == ch) {
                  ++s_index;
              }
              if (s_index == s.size()) {
                  return true;
              }
          }
          return false;
      }
  };
  ```

  ただ early return がなくなっている。最後までいかないとわからない

  - もっと簡潔に書くのであればこう。ただこちらも最後までいかないとわからない。

  ```cpp
  class Solution {
  public:
      bool isSubsequence(std::string s, std::string t) {
          int s_index = 0;
          for (char ch : t) {
              if (s_index < s.size() && s[s_index] == ch) {
                  ++s_index;
              }
          }
          return s_index == s.size();
      }
  };
  ```

無限ループ。競争みたい。確かに書けるのだけど、いきなり `while (true)` が来るのは唐突に見える。

```cpp
class Solution {
public:
    bool isSubsequence(std::string s, std::string t) {
        int s_index = 0;
        int t_index = 0;

        while (true) {
            if (s_index == s.size()) {
                return true;
            }
            if (t_index == t.size()) {
                return false;
            }

            if (s[s_index] == t[t_index]) {
                ++s_index;
            }
            ++t_index;
        }
    }
};
```

- [参照](https://github.com/olsen-blue/Arai60/pull/58/changes)

`chr` → `c` / `ch` 

- [参照](https://github.com/olsen-blue/Arai60/pull/58/changes#r2033292415)

正規表現！確かにこうなるか。
> これは、正規表現で s の文字のすべての間に .* を挟み込んで、マッチすればいいので、一回舐めれば解けそうですね。

- [参照1](https://discord.com/channels/1084280443945353267/1201211204547383386/1231637671831408821)、[参照2](https://github.com/fhiyo/leetcode/pull/55/changes)
  - 1つ目の後にあるように、特殊文字のエスケープが必要になるなどややこしい。
- `regex.cpp` に書いてみたが、`s` と `t` が長い時にTLEになってしまった。
  - C++ の regex は遅いとどこかにあった、仕方ないのだろう
    - バックトラッキング型の実装とか、そういうことだったかな（c.f., [このコメント](https://github.com/goto-untrapped/Arai60/pull/19#discussion_r1597451964)）

## Step 3

`step2.cpp` と同じようにした。
