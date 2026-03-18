# 3. Longest Substring Without Repeating Characters

## Step 1

Sliding window というのは聞いたことがないが、字面からなんとなくイメージがつく気がする。文字数を $s = 1, 2, \dots$ と増やしていって、その長さの枠で文字列を左から舐める。ユニークな文字だけで枠を埋められたら $s$ を増やす。複数回登場する文字がないような最大の $s$ を返す。こういう発想でできないだろうか？

- ちょっと考えてみたが、部分文字列を作って重複を確認するところで走査が必要になって時間がかかってしまいそう。走査をせずにできないかしら。
- 新しく出てきた文字が重複しているかどうかを判定する感じにすると良いかも？

`step1.cpp` に書いた。`left, right` で囲まれた範囲の文字を `unordered_set` に入れておく(重複が許されない)。文字数を増やすのではなく、右側を動かしていって、重複を見つけたら重複が無くなるまで左側をずらす。重複がなければ右側を追加して最大長さを更新する。

- 時間計算量 $O(n)$、空間計算量 $O(n)$。
- これが sliding window なのか。なるほど。

## Step 2

`characters.size()` を使って文字数カウントをするという手もあるが、一工夫いるのか。
> using_characters.size()をintにキャストせずにそのままmaxに渡すと、max関数にintとsize_t（leetcodeの環境ではunsigned longみたいです）が渡されることになって（少なくともleetcodeの環境上では）エラーになってしまいました。

- [参照](https://github.com/potrue/leetcode/pull/48/changes)
- 型推論に失敗するので `std::max<int>` としてあげるのが一工夫。

総当たりでやるとこんな感じ。一応回る。s

```cpp
#include <algorithm>
#include <unordered_set>
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int max_length = 0;

        for (int left = 0; left < s.size(); ++left) {
            std::unordered_set<char> characters;
            for (int right = left; right < s.size(); ++right) {
                if (characters.contains(s[right])) {
                    break;
                }
                characters.insert(s[right]);
                max_length = std::max(max_length, right - left + 1);
            }
        }
        return max_length;
    }
};
```

`map` を使っている人もいるが重複を許さないので `set` で良いかなあと思う。ここで辞書使うありがたみってなんだろう？

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/52/changes)
- 調べていてなるほど、と思った。登場回数ではなく index を値にする感じか。
  > なるほど。seen_char_to_index = {}という辞書で、charをキーにすれば存在有無が確認できて、値でindexを取り出せば、index　+ 1の位置にジャンプできる。こっちの方が効率良さそうで良いですね。
  - [参照](https://github.com/olsen-blue/Arai60/pull/49/changes)

`left / right` や `begin / end` が特定の形式の区間と紐づいて認識されるかもという話が。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/52/changes#r2003497726)

## Step 3

3回書いた。
