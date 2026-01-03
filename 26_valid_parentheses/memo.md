# Step 1

## 1回目

### コード

まず、`unordered_map` で有効な括弧の組み合わせを表現した。
最初のアプローチは、文字列を左から探索して次の文字が対応する括弧でなかった場合に `false` を返すというものにした。
この場合、`([])` のようなケースを判別できないので良くない。
次に、左と右から探す方法を考えてみたが、それだと今度は左右対称でないケースが判別できなくなる。
このタイミングで、有効な括弧が順番に出てくるケースとネストされているケースとをまとめて考える必要があることに気づく。
ここで解答を見る。

```cpp
class Solution {
public:
    bool isValid(string s) {
        unordered_map<char, char> parentheses;
        parentheses = { {'(', ')'}, {'{', '}'}, {'[', ']'} };

        int i = 0;

        while (i < s.length()) {
            
            char char_next = s[i+1];

            if (parentheses.contains(s[i]) && char_next != parentheses[s[i]]) {
                return false;
            }

            i++;
        }

        return true;
    }
};
```

### メモ

- `char` と `string` の扱い方の違いに注意する。

- 長さがわかっているので `while` を使う必要はなく、`for` で良いのでは？

- [`stack` を使う発想](https://github.com/hemispherium/LeetCode_Arai60/pull/8/commits/7ec3c976583de6f71ef26b69b067537d9c41d58c)が出てこなかった。
  > 括弧の左側をstackに積んでいって、stackの一番上に対応する右側が来た場合popする、そうでない場合はreturn falseするという感じで解いた。作業がすべて終わってstackが空でない場合もfalse。stackの名前を何にするか迷ったがいい名前が思いつかなかったのでstとしておいた。

  - [C++ レファレンス](https://cpprefjp.github.io/reference/stack/stack.html)。とりあえず出た要素を手元に置いておき、対応するものが来たらまとめて捨てる、最後まで通ったら `true` を返すという感覚っぽい。このやり方だと順番に来るケースも左右対称なケースも処理できる。

    - Last in, first out (LIFO)

## 2回目

### コード

step1.cppに書いた。

# Step 2

## コード

step2.cpp に記載。

- ネストが深いのを修正する。`continue`で早期にリターンする。

- `for` loop の中で `return false` が2回来ているのが気持ち悪い。以下のようにすれば one-liner 二つで見やすくなる。自然言語だと「閉じ括弧と対応する開き括弧を stack から探すとき、空なら false を返す、空でなくても一番上の要素と一致しなければ false を返す」
```cpp
if (st.empty()) return false;
if (pairs_parentheses.at(st.top()) != c) return false;
st.pop();
```

## 勉強

- `contains` を使えるのは C++20 から。

- [一文字変数の使い方](https://github.com/konnysh/arai60/pull/6/files#r1843060460)。長く使わないものならいいかな、くらいの感覚。

- [map + [] と const + at](https://github.com/konnysh/arai60/pull/6/files#r1856679268)。`const at` の方が安全ではという気がしてきた。

  - `[]` を使って存在しないキーの要素にアクセスすると、新しく要素を作ってその参照を返すのに対し、`at`でアクセスすると例外が投げられる。

  - const修飾されたオブジェクトでは、const付きのメンバー関数のみを基本呼び出せる。

- [`push` と `embrace`](https://github.com/Ryotaro25/leetcode_first60/pull/7/files)。`push` が値をコピー・移動するのに対し、`emplace`は in-place で作成する。

- 連想するもの。

  > valid parentheses は、チョムスキー階層、タイプ-2、文脈自由文法だから、プッシュダウンオートマトンで書ける、を多分連想します。

  > これは、全部一つのことを言っていますが、これは常識です。正規言語、正規文法、有限オートマトン、と対比されます。

  - [プッシュダウンオートマトン](https://discord.com/channels/1084280443945353267/1206101582861697046/1216945010189144085)。スタックが一つあるような計算モデルのこと。

    - [Wikipedia](https://en.wikipedia.org/wiki/Pushdown_automaton)より：

    > The term "pushdown" refers to the fact that the stack can be regarded as being "pushed down" like a tray dispenser at a cafeteria, since the operations never work on elements other than the top element.

  - チョムスキー階層。「C言語は文脈依存ではあるはずだからType-2文法？」といっている人がいた。
  

    | タイプ | 文法 |　言語 | 計算モデル
    | Type-3 | 正規文法 | 正規言語 | 有限オートマトン
    | Type-2 | 文脈自由文法 | 文脈自由言語 | プッシュダウンオートマトン
    | Type-1 | 文脈依存文法 | 文脈依存言語 | 線形拘束オートマトン
    | Type-0 | 制限なし | 再帰的可算言語 | チューリングマシン

  - 有限オートマトンが持つ状態は有限のため、無限の深さを持つ入れ子構造を覚えられない。

- [再帰下降構文](https://discord.com/channels/1084280443945353267/1235829049511903273/1238815737548898346)。全然知らないので色々調べる。

  ```cpp
  /*
  parens = ('(' parens ')' | '{' parens '}' | '[' parens ']')*
  */
  class Solution {
  public:
      bool isValid(string s) {
          int i = 0;
          auto consume = [&](char c) {
              if (i < s.size() && s[i] == c) {
                  ++i;
                  return true;
              }
              return false;
          };
          function<bool()> parens = [&]() {
              while (true) {
                  if (consume('(')) {
                      if (!(parens() && consume(')'))) {
                          return false;
                      }
                  } else if (consume('[')) {
                      if (!(parens() && consume(']'))) {
                          return false;
                      }
                  } else if (consume('{')) {
                      if (!(parens() && consume('}'))) {
                          return false;
                      }
                  } else {
                      return true;
                  }
              }
          };
          return parens() && i == s.size();
      }
  };
  ```

  - [Wikipedia](https://en.wikipedia.org/wiki/Recursive_descent_parser)より。

  > In computer science, a recursive descent parser is a kind of top-down parser built from a set of mutually recursive procedures (or a non-recursive equivalent) where each such procedure implements one of the nonterminals of the grammar. Thus the structure of the resulting program closely mirrors that of the grammar it recognizes.

    - `parens()` が非終端記号になっている。

# Step 3

step3.cpp に書いた。 "parentheses" は "()" しか指さないという...。"brackets"に変えた。
