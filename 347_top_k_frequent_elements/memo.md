# Step 1

## 1回目

### コード

map か priority queue か、どちらかを使って書いてみようと考えたが思いつかなかった。
出てきた値を map に追加していって値と出現回数をまとめたものを作るところまで考えて、
その後どうすれば良いかが分からなくなった。

### メモ

分からなくてちょっと調べる。すると、

- [アプローチ](https://github.com/irohafternoon/LeetCode/pull/11/commits/f07bc0eec037c1c6e72b16c38dc6fad3ca22a145)。
  > 昇順にソートされたsetに<-1*出現回数,値>のpair型を入れ、小さい順にK回取り出して、vectorにpushする

  - この文を見て、map をひっくり返せばいいじゃん、となった。

  - ひっくり返した map の最初から最後まで見ていく。
  map の value には各 count に対応する値が potentially 複数入っているので、for loop で繋ぐ。
  push_back した後にkの値を減らしていって、0になった時点で break する。

  - この発想で2回目のコードを書く。

## 2回目

### コード

とりあえず、考えて書けた。
3つ目のloopの中でmapを端から端まで見る・その各ステップで unique value を見るというのをやっているが、
ここをもう少し単純にできないか？

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> value_count; 
        map<int, vector<int>, greater<int>> count_value; 
        vector<int> top_k_frequent; 

        for (int num : nums) {
            value_count[num]++; 
        }

        for (auto &[value, count] : value_count) {
            count_value[count].push_back(value); 
        }

        for (auto it = count_value.begin(); it != count_value.end() && k > 0; ++it) {
            for (int value : it->second) {
                top_k_frequent.push_back(value);
                k--; 

                if (k == 0) {
                    break;
                }
            }
        }

        return top_k_frequent; 
    }
};
```

# Step 2

## 勉強

名付け。

- [辞書の名付け](https://github.com/irohafternoon/LeetCode/pull/11/commits/f07bc0eec037c1c6e72b16c38dc6fad3ca22a145#r2024946024)。
`key_to_value` という形が良いとのこと。確かに。

- [使っていない変数](https://github.com/Hurukawa2121/leetcode/pull/9/files#r1885068470)。[こういう議論](https://stackoverflow.com/questions/40673080/stdignore-with-structured-bindings)も。
> [[maybe_unused]] や __maybe_unused などがあります。

使うオブジェクト。

- [参考](https://github.com/irohafternoon/LeetCode/pull/11/commits/f07bc0eec037c1c6e72b16c38dc6fad3ca22a145)。
`set` に pair 型を入れている。

- [型推論](https://en.cppreference.com/w/cpp/language/class_template_argument_deduction.html)。

- 試しに priority queue を使って書いてみよう。なんかあまり変わらないが...。
  ```cpp
  #include <vector>
  #include <queue>
  #include <map>

  class Solution {
  public:
      vector<int> topKFrequent(vector<int>& nums, int k) {
          map<int, int> value_to_count; 
          priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> count_and_value; 

          for (int num : nums) {
              value_to_count[num]++; 
          }

          for (auto &[value, count] : value_to_count) {
              count_and_value.push({count, value}); 
              if (count_and_value.size() > k) {
                  count_and_value.pop();
              }
          }

          vector<int> top_k_frequent;
          while (count_and_value.size() != 0) {
              top_k_frequent.push_back(count_and_value.top().second);
              count_and_value.pop();
          }

          return top_k_frequent;
      }
  };
  ```

制約について。

- [参考](https://github.com/irohafternoon/LeetCode/pull/11/commits/f07bc0eec037c1c6e72b16c38dc6fad3ca22a145#r2025258371)。
例えば、k が num の長さよりも大きいケースを想定するとどうなるか？ step 1のアプローチだと値が先になくなってしまう。

構造体を書く、比較演算子を定義する。

- [参考](https://github.com/irohafternoon/LeetCode/pull/11/commits/f07bc0eec037c1c6e72b16c38dc6fad3ca22a145#r2028846527)。
コメントだけ読んで、あまりにも眠くて翌日に回した。
  - 例えば、以下のようなことをする。構造体を作って意味のわかりやすい名前をつけた上で、新しく要素を入れた時にソートされるようにしてあげるということ。
    ```cpp
    struct CountAndScore {
      int count;
      int score;

      bool operator<(const CountAndScore& other) const {
        return count > other.count;  // count の降順
      }
    };
    ```

  - 一般には `戻り値型 operator演算子(引数) 修飾子`という感じ。

Quick select。

- [参考](https://discord.com/channels/1084280443945353267/1183683738635346001/1185972070165782688)。常識の範囲なので、後で見ておく。

メンバ変数など

- [二度呼び](https://docs.google.com/document/d/11HV35ADPo9QxJOpJQ24FcZvtvioli770WWdZZDaLOfg/edit?tab=t.0)。メンバ変数を使うと2回呼び出せないことがある。あとは、スレッド並列性の問題なるものがある。以下引用。確かに、関数の中で持っておいた方が良いこともあるのか。
  > 複数スレッドが同時にtopKFrequent()を呼んだ際にprivateのデータメンバを変更する際に競合が発生してしまうということ

## コード

元の方針のまま、名付けやループのロジック、初期化のタイミングを変えることにした。
あと、`#include <...>` をちゃんと書くことにした。

```cpp
#include <vector>
#include <map>

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int, int> value_to_count; 
        map<int, vector<int>, greater<int>> count_to_value; 
        vector<int> top_k_frequent; 

        for (int num : nums) {
            value_to_count[num]++; 
        }

        for (auto &[value, count] : value_count) {
            count_to_value[count].push_back(value); 
        }

        while (count_to_value.size() != 0 && k > 0) {
            auto it = count_to_value.begin(); 

            for (int value : it->second) {
                top_k_frequent.push_back(value); 
                k--;
            }

            count_to_value.erase(it);

        }

        return top_k_frequent; 
    }
};
```

# Step 3

問題なくかけた。
