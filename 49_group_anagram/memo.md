# Step 1

## 1回目

Anagram と palindrome / 回文を間違えていて変なコードを書いていた。
方針としては似ているので書いておく。

strsを左から見ていって、それぞれの要素ごとに対応する文字列を探す。
見つかったら2つをベクトルにして返り値ベクトルに入れる。
1対1対応するので一度見た要素は見なくても良いから、見る要素を減らした2重ループでやれば良い。

同じ要素が複数strsに入っている場合のことを考えているあたりであれ？となり、やめた。

## 2回目

### コード

アナグラムの場合は対応する要素が一つに定まらない。
ある文字のセットにアナグラムとなる単語群が対応すると考えると、
文字セットをキー、単語群を値とするunordered_mapが使える。

```cpp
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::unordered_map<std::string, std::vector<std::string>> element_to_strings; 

        for (int i = 0; i < strs.size(); i++) {
            std::string str = strs[i]; 
            std::sort(str.begin(), str.end()); 
            element_to_strings[str].push_back(strs[i]); 
        }

        std::vector<std::vector<std::string>> anagrams; 
        for (auto& [key, value] : element_to_strings) {
            anagrams.push_back(value); 
        }

        return anagrams; 
    }
};
```

- value の集合だけ返せたらよかったんだが、C++だと使えない

- 文字配列の長さを n、文字の長さを $k$ として、時間計算量は $O(k \log k)$、空間計算量は $O(nk)$？
今ひとつまだ見積もりの方法が判然としていない。

# Step 2

## 勉強。

map / unordered_mapについて。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/13/commits/2416b565cd8a2a983b8cab3543d1b0d32dbc4649#r1641601394)。一度それぞれ実装してみないと体感得られなさそう。

文字とその出現回数によって各グループを特徴づける方法もある。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/13/commits/2416b565cd8a2a983b8cab3543d1b0d32dbc4649#diff-fa71c04d31db1e2257ec0c477cb61008667fa7a8c9619e85859e3a15e2f76365)。ちょっと知らないことが多いので、後で戻ってくることに。

- Step 1 の方法に比べると冗長そうな感じがする。strsに含まれる単語の中に入っていない文字についてまでキーを用意してあげている。

[無駄なコピーを減らす](https://github.com/Ryotaro25/leetcode_first60/pull/13/commits/2416b565cd8a2a983b8cab3543d1b0d32dbc4649#r1636916877)。

- [push_back](https://en.cppreference.com/w/cpp/container/vector/push_back)、[move](https://en.cppreference.com/w/cpp/utility/move.html)。moveを使うとコピーするのではなく動かせる。

  - [moveについて](https://cpprefjp.github.io//lang/cpp11/rvalue_ref_and_move_semantics.html)。読む。

- [記法](https://discord.com/channels/1084280443945353267/1183683738635346001/1188062188645122069)。


# Step 3

同じ方針で書いた。

# Step 4

## Countで書く

### コード

調べながら`count.cpp`に書いた。色々わからなかったことがあるのでメモしておく。

- [`ArrayHash`]構造体。アルファベットの出現回数を与えられると、それに対応する整数を一つ返す。

  - `result = result * 31 + x` としているが、最低限 x が取りうる最大値よりも大きければ混ざらないことが保証される（ここでは strs の要素の長さよりも長ければ良いか？）。

- [`size_t`](https://en.cppreference.com/w/cpp/types/size_t.html): 符号なし整数型で、その環境で扱える最大のオブジェクトサイズを最大値とする。固定サイズではない。

  > std::size_t can store the maximum size of a theoretically possible object of any type (including array)

  - Indexing などに使われるとあり、`unsigned int`と対比されている。インデックスの数が多くなった場合に壊れづらいということだろう。

    - 試しに、`int` を使って書いてみると次のようなエラーが出る。長すぎるということ。32ビット環境では $-2^{31}$から$2^{31} - 1$ くらい。
    > Line 29: Char 33: runtime error: signed integer overflow: 887504642 * 31 cannot be represented in type 'int' (solution.cpp)

  - もちろんいくらでも表現できるわけではなく、「環境で扱える最大のオブジェクトサイズ」を超えたものを作ろうとするとうまくいかない。現実のメモリ空間に対応した上限がある。

- `c - 'a'` のところ、何をしているのか最初はわからなかったので、調べた：`char` は内部では整数型であり、ASCIIコードを使ってマッピングされている。`c - 'a'`というのはcがaに対応するコードから何番目になっているかを計算している。例えば`'a' - 'a'`であれば0番目を指すことになる。

- [無駄なコピーを減らす](https://github.com/Ryotaro25/leetcode_first60/pull/13/commits/2416b565cd8a2a983b8cab3543d1b0d32dbc4649#r1636916877)。この話はもう少しちゃんと理解しておきたい。
