# 139. Word Break

## Step 1

`s` の文字を左から順に繋げていって、都度都度 `wordDict` に文字列が入っているかどうかを確認し、あったら消して文字列を作り直す。最後まで行ったところで文字列を消すことになった場合 `true` を返す。

- `s = "aaaaaaa", wordDict = ["aaaa","aaa"]` でだめだった。`"aaa"` 2つに反応してしまう。

- Reuse できなければ辞書の方にチェックを入れていけば良いのだがそうではない...。

- 時間計算量は $O(N \times M)$、空間計算量は $O(N)$。

```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if (s.empty()) {
            return false;
        }

        string strs = "";
        for (int i = 0; i < s.size(); ++i) {
            strs += s[i]; 
            auto it = std::find(wordDict.begin(), wordDict.end(), strs); 
            if (it != wordDict.end()) {
                strs = "";
                if (i == s.size() - 1) {
                    return true;
                }
            }
        }

        return false;
    }
};
```

DP table を作ってみる。`i` 文字目以降を辞書の単語だけで最後まで分割できるかで `true` と `false` を入れていく。`step1.cpp` に書いた。

- 元々のやり方にも当てはまるが、hash table に辞書を変えておけば走査が早くなる。

別のやり方として、`i` 文字目の時点でそこまでの文字列が分割できるかを見ていく方法がある。最後まで見切れば文字列全体が分割できるか判断できる。`bottomup.cpp` に書いた。

- 時間計算量 $O(N^2)$、空間計算量 $O(N)$？ → 時間の方は中にさらに `substr` による比較が入るので $O(N^3)$ だ...。
- `1 <= s.length <= 300`、`1 <= wordDict.length <= 1000` なので大体 $10^7$ ステップくらいで、0.1sくらい？

## Step 2`

`bottomup.cpp` のやり方が一番わかりやすいと思ったので `step2.cpp` にはそれを書く。

### 勉強

[参照](https://github.com/potrue/leetcode/pull/39/changes#:~:text=%2B-,%23%23%20%E6%9C%80%E7%B5%82%E3%82%B3%E3%83%BC%E3%83%89,-82)：`string_view` を使ってコピーを減らしている。

- [名付けの工夫についてのコメント](https://github.com/potrue/leetcode/pull/39/changes#r2264788505)

[参照](https://discord.com/channels/1084280443945353267/1200089668901937312/1221644164576444527)：正規表現？

- 正規表現で作れるというのはわかる。
- 正規表現の実装はバックトラック系とそれ以外に分けられる（[参照](https://www.akenotsuki.com/misc/srell/relibs.html)）
  - バックトラック：ある選択肢を試して、ダメなら戻って別の選択肢を試すというアプローチ。自分の最初のコードが引っかかったようなテストケースでまさに引っかかっている
- C++ の `std::regex` はバックトラック型らしい。

[参照](https://github.com/katsukii/leetcode/pull/11/changes#:~:text=%23%23%23%20%E8%A7%A3%E6%B3%953.%20Trie%EF%BC%88%E3%83%88%E3%83%A9%E3%82%A4%E6%9C%A8%EF%BC%89%2B%20DP)：トライ木？

- トライ木：prefix の共通部を木構造でまとめたデータ構造。
  - [参照](https://ja.wikipedia.org/wiki/%E3%83%88%E3%83%A9%E3%82%A4_(%E3%83%87%E3%83%BC%E3%82%BF%E6%A7%8B%E9%80%A0))
- この問題であれば、辞書をトライ木に変えて、文字列をみるときにトライ木に当てはめながら見ていく。トライ木の終端に到達したら `true` を返す。
- 部分文字列を作って比較する必要がないのと、ポイントを動かしていくのとで速い。
- LLMに手伝ってもらいながら `trie.cpp` に書いた。

## Step 3

m
