# Step 1

## 1回目

### コード

文字をキー、登場したインデックスを値に持つ map を作成する。
各キーについて map の値を順番に見ていき、長さが1であるようなもののうち最小のものを返す。なければ -1 を返す。

以下のコードで通った。1回目で方針が立ってコードも通るのは初めてなのでちょっと嬉しい。

```cpp
#include <map>
#include <string>
#include <vector>

class Solution {
public:
    int firstUniqChar(std::string s) {
        std::map<char, std::vector<int>> char_to_indices; 
        for (int i = 0; i < s.size(); i++) {
            char char_i = s[i]; 
            char_to_indices[char_i].push_back(i); 
        }

        int idx_smallest = 100000 + 1; 
        for (auto& [key, value] : char_to_indices) {
            if (value.size() == 1 && value[0] < idx_smallest) {
                idx_smallest = value[0]; 
            }
        }

        if (idx_smallest == 100000 + 1) {
            idx_smallest = -1; 
        }
        return idx_smallest; 
    }
};
```

### メモ

- 文字列の長さを $n$、文字の種類を $k$ として、時間計算量 $O(n \log k)$、空間計算量 $O(n)$。

- `idx_smallest` は長さの最大 $10^5$ よりも1大きくして初期化した。
同じ書き方をするのであれば、`cmath`ヘッダを入れて `std::pow(10, 5)`と書くのでも良い。
最初は `idx_smallest = -1` で初期化しようとしたが、map の値を見ていくときに困るかなと思って変えた。

  - 以下のように書くと最初の比較で詰まってしまう。ループの一つ目の要素だけを特別扱いすれば良いのだが、どっちの方がいいのかはケースバイケースか。
  ```cpp
  int idx_smallest = -1; 
  for (...) {
    if (value.size() == 1 && value[0] != -1 && value[0] < idx_smallest) {
      idx_smallest = value[0]; 
    }
  }
  ```

# Step 2

## 勉強

最初にソートする方法を考えている人もいた。

- [参照](https://github.com/kazukiii/leetcode/pull/16/commits/67f051bdc0384cd5afea47037e8c2a274156d7b0)。

2回とも文字列を左から見れば、インデックスを保持する必要はない。
```cpp
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> char_to_count;
        for (int i = 0; i < s.size(); i++) {
            char_to_count[s[i]]++;
        }

        for (int i = 0; i < s.size(); i++) {
            if (char_to_count[s[i]] == 1) return i;
        }
        return -1;
    }
};
```

- [参照](https://github.com/kazukiii/leetcode/pull/16/commits/67f051bdc0384cd5afea47037e8c2a274156d7b0#diff-ab5f3d992bba7dfdbae5fb89c6211844968879aaa279be404afd515fc3d9229d)。

- 2回目のループでは左から文字列を出ていって、登場回数が1回のものに出会ったら即それを返せば良い。こちらの方がシンプルだと思う。

- 最初方針を考えた時にmapを`char_to_count`にするのも検討したのだが、何かが引っかかってやめてしまっていた。おそらく、2回目のループをmapの要素に対して行うことが念頭にあったからだと思う。

[マジックナンバー](https://github.com/kazukiii/leetcode/pull/16#discussion_r1650394921)。

- `100001` はマジックナンバーであり、文脈が共有されていないと可読性を下げてしまう。`INT_MAX`や [`std::numeric_limits::max()`](https://en.cppreference.com/w/cpp/types/numeric_limits.html)が適切そう。

- 見つからなかった場合の返り値にも名前をつけておくとか。

その他の点について。

- 現在保持している要素と新しく見つけた大きさ1の要素とを比較する場合、`std::min(idx_smallest, value[0])` みたいにした方が良いかも。条件文が長すぎないように。

- [二重ループで全探索 + 枝切りの方法](https://github.com/irohafternoon/LeetCode/pull/17/commits/5c32a510c26e07bfd7bd6d0de124fc4ad0f4c95b#diff-fb81ed53fb67c4a2f6eb35afad3435b834be248cd1ab737cb0ab7526572c9a69)。
  ```cpp
  #include <map>
  #include <string>
  #include <vector>

  class Solution {
  public:
      int firstUniqChar(const std::string& s) {
          for (int index1 = 0; index1 < s.size(); index1++) {
              bool is_unique = true;
              for (int index2 = 0; index2 < s.size(); index2++) {
                  if (index1 != index2 && s[index1] == s[index2]) {
                      is_unique = false;
                      break;
                  }
              }
              if (is_unique) {
                  return index1;
              }
          }
          return -1;
      }
  };
  ```

- [Doubly linked list を使う方法](https://github.com/irohafternoon/LeetCode/pull/17/commits/5c32a510c26e07bfd7bd6d0de124fc4ad0f4c95b#diff-fb81ed53fb67c4a2f6eb35afad3435b834be248cd1ab737cb0ab7526572c9a69)。あとで書いてみる。
> mapでcharに対するノードの場所を覚えておき、カウントが2以上になれば、そのノードを切り離して脱落させ、prevをnextに繋ぎ直す

  - 左から読んでいって、「1回だけ出た文字だけを順番に並べた列」の先頭に関心がある。この並んだ列を linked list を使って表現する。

  - Doubly linked list + `map<char, node*>` + `set` / `map<char, bool>`を使う。それぞれ、列・各文字のリスト上の居場所・状態管理に対応。

  - 初期のリストは head と tail のみがつながっている。左から見ていって一文字ずつ間に入れていく。被りが出たらそのノードを切り離す。最後まで行ったところで最初のユニーク文字を返す。

  - [LRU cache と関連しているそう](https://github.com/irohafternoon/LeetCode/pull/17/commits/5c32a510c26e07bfd7bd6d0de124fc4ad0f4c95b#r2039457825)。LRU cache = least recently used cache. 

# Step 3

問題なく書けた。

# Step 4

マジックナンバーなど

- 上から評価していくときに `int above_maximum =  100001` としておくとよさそう。

- [参照](https://docs.google.com/document/d/11HV35ADPo9QxJOpJQ24FcZvtvioli770WWdZZDaLOfg/edit?tab=t.0#heading=h.jdtk9v35bca4)。
ある時点での given な制約を当てにしすぎないほうが良いということ。
