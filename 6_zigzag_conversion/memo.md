# 6. Zigzag Conversion

## Step 1

与えられた文字列を指定の行数でジグザグになるように書き、それを行ごとに読んで返す。

- 制約：`1 <= s.length <= 1000, 1 <= numRows <= 1000`, `s` には大文字・小文字とカンマ・ピリオドが含まれる。

文字列をジグザグに配置してから1行ずつ読む？これだとちょっと効率悪そう。

- 各列に入る文字数は `numRows` ないし 1 で、1 の数は `numRows - 2`。
- 1 の置く位置は `numRows - 1` からスタートして 1 まで。空いているところには空文字を入れる。
- 配置するのに配列を一度舐めた後、テーブルを by row and column で見なければいけないので効率が悪いか。時間計算量が `s` の長さを `N` として $O(N \times numRows)$になる？ただ実際には行数・列数がトレードオフになるのでそこまで悪くないかも。

40分くらいで次のコードを書き、WA。答えを見る。

```cpp
class Solution {
public:
    std::string convert(std::string s, int numRows) {
        if (numRows == 1) {
            return s;
        }
        
        int cycle = 2 * numRows - 2;
        int numCols = (s.size() / cycle + 1) * (numRows - 1);
        std::vector<std::vector<char>> zigzag_table(
            numRows, 
            std::vector<char>(numCols)
        ); 
        int num_mid_location = numRows - 2;
        int r = 0;
        int c = 0;

        for (int i = 0; i < s.size(); ++i) {
            // columns where all rows have a character
            if (c % (numRows - 1) == 1) {
                zigzag_table[r][c] = s[i];
            } else if (r == num_mid_location) {
                zigzag_table[r][c] = s[i];
                if (num_mid_location == 0) {
                    num_mid_location = numRows - 2;
                } else {
                    --num_mid_location;
                }
            }

            // proceed to the next character
            ++r;
            if (r == (numRows - 1)) {
                ++c;
                r = 0;
            }
        }
        
        // Read the table created above
        std::string zigzag_s; 
        for (r = 0; r < zigzag_table.size(); ++r) {
            for (c = 0; c < zigzag_table[0].size(); ++c) {
                zigzag_s += zigzag_table[r][c];
            }
        }

        return zigzag_s;
    }
};
```

- 修正して `step1.cpp` に書いた。
- 時間計算量 $O(R \times N)$, 空間計算量 $O(R \times N)$。テーブルに空文字が多く無駄が多い気がする。

## Step 2

なるほど、列の情報はいらないのか...。

```cpp
#include <string>
#include <vector>
class Solution {
public:
    string convert(std::string s, int numRows) {
        if (numRows == 1) {
            return s;
        }

        std::vector<std::string> strings_by_line(numRows);
        int line = 0;
        int direction = 1;  // 1: going down, -1: going up
        
        for (char ch : s) {
            strings_by_line[line].push_back(ch);
            if (line == 0) {
                direction = 1;
            } 
            if (line == numRows - 1) {
                direction = -1;
            }
            line += direction;
        }

        return std::accumulate(strings_by_line.begin(), strings_by_line.end(), string());
    }
};
```

- [参照](https://github.com/potrue/leetcode/pull/60/changes)
- `direction` が方向とインデックスの両方を表しているのは少し気持ち悪いかも。
  - [議論](https://github.com/olsen-blue/Arai60/pull/61/changes)がありそう

`goto` は初めて見た。コメント / 以下の記載にもあるように、どうしようもない時以外は使わないほうが良いのだろう。
> Used when it is otherwise impossible to transfer control to the desired location using other statements.

- [レファレンス](https://en.cppreference.com/w/cpp/language/goto.html)
- [コメント](https://github.com/potrue/leetcode/pull/60/changes#r2311880080)

周期性を使う方法でももっと無駄がないものがある。

- [参照](https://github.com/potrue/leetcode/pull/60/changes#diff-c371c64edbed3a76c37210ebf76e8f3db29e6bf854ff6a98b107e640008ab1f0R132-R138)

`rope` というデータ構造があり、標準ライブラリには載っていない。[これ](https://www.geeksforgeeks.org/cpp/stl-ropes-in-c/)を読んだがよくわからなかった。二分木で、葉っぱが文字列と長さを持っており、ノードは左部分木の長さの合計を持っている。なので、子供が2ついるノードは文字列を分割していることになる。
> A rope is a binary tree where each leaf (end node) holds a string and a length (also known as a “weight”), and each node further up the tree holds the sum of the lengths of all the leaves in its left subtree. A node with two children thus divides the whole string into two parts: the left sub-tree stores the first part of the string, the right subtree stores the second part of the string, and a node's weight is the length of the first part.

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/66/changes#r2020118072)

` ` で table を初期化していたけど、空文字 '\0' の方が良いな。入力の制約上今は良いけど。
> // rustはempty charがないので' 'で初期化

- [参照](https://github.com/Yoshiki-Iwasa/Arai60/pull/65/changes)

## Step 3

`step2.cpp` と同じやり方でやった。
