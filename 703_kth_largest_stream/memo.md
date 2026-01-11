# Step 1

## 1回目

### コード

次のような方針を考えた。

- まず、最初は null を返すように返り値を初期化する

- 最初に add されたらその時点でk番目に大きい値を返り値に与える
        
- 以後、add されるたびにk番目に大きい値を次の手順で計算し直す
  1. addされた値が現在のk番目よりも大きいか小さいかを判別する
    - 小さければそのままの値を返す
    - 大きければ2. に進む
  2. addされた値をk-1番目に大きい値と比較する
    - addされた値の方が大きければk-1番目の値を返す
    - addされた値の方が小さければその値を返す

クラスの書き方が全く分からず書けなかった。

### メモ

- k-1番目に大きい値が常にわかることをどうやって保証するのか？

- 上の点を繰り返し考えていくと、結局上位 k 個を毎回把握している必要があるとわかる。

- これを実現するために [priority queue](https://cpprefjp.github.io/reference/queue/priority_queue.html)を使う。
例えば、`std::priority_queue<int> que;` であれば `int` を要素に持つ優先順位付きキュー。
デフォルトでは内部のコンテナは `vector`、ソートは降順になる。

  - 以下のように書くと昇順にできる。
  ```cpp
  std::priority_queue<
      int,                // 要素の型はint
      std::vector<int>,   // 内部コンテナはstd::vector (デフォルトのまま)
      std::greater<int>   // 昇順 (デフォルトはstd::less<T>)
    > que;
  ```

  - 今回のケースであれば、上位 k 個の要素を昇順にセットした priority queue を用意して、

## 2回目

### コード

```cpp
class KthLargest {
public:
    int K; 
    priority_queue<int, vector<int>, greater<int>> top_k_vals;

    KthLargest(int k, vector<int>& nums) : K(k) {
        for (int x : nums) {
            add(x);
        }
    }
    
    int add(int val) {
        top_k_vals.push(val);
        if (top_k_vals.size() > K) {
            top_k_vals.pop();
        }
        return top_k_vals.top();
    }
};

```

### メモ

- `K(k)` でメンバ変数の初期化を行なっている。

- 最初の2行は `private` の中に置いた方が良いかも。
`top_k_vals` はデフォルトコンストラクタを持っているので必要ないが、そうでないケースでは初期化リストに含める必要がある。

  - [クラスメンバにする理由](https://github.com/maeken4/Arai60/pull/8#discussion_r2127968692)。繰り返し`add`を呼ぶというのが今回のポイント？

# Step 2

## 勉強

クラスのメンバ変数の名前には最後に `_` をつける。

- 参照：https://google.github.io/styleguide/cppguide.html#Variable_Names

`K` はスコープが長い割に名前が短すぎるか。

- 参照：https://github.com/maeken4/Arai60/pull/8#discussion_r2129583630

- `val_threshold`とか良さそう。

以下のように、各時点において priority queue に入っているすべての要素を考えて、k 番目より大きい値をすべてpopする方法がある。

```cpp
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) 
        : kth(k), scores()
    {
        for (int num : nums) {
            scores.push(num);
        }  
    }

    int add(int val) {
        scores.push(val);
        for (std::size_t i = scores.size(); i > kth; i--) {
            scores.pop();
        }
        return scores.top();
    }

private:
    int kth;
    std::priority_queue<int, std::vector<int>, std::greater<int>> scores;
};
```

- 参照：https://github.com/5103246/LeetCode_Arai60/pull/8/commits/47a331c2c1be203a67a24bb36b7d88833c60bc28

- 書いた方は次のように書いている。全要素を考慮するのをやめると評価する回数が抑えられるということだと理解した。[このコメント](https://github.com/hemispherium/LeetCode_Arai60/pull/9#discussion_r2621522371)の「無駄なpop」というのもこの文脈にある？
  > step1の解き方だと、空間計算量がO(nums.length)だが、下記のコードだとO(k)になる。
  > kがnums.lengthより十分小さい場合などを考えるとこちらの解き方が良いと感じた。

`map` を使った書き方がある。値ごとの出現回数を降順に（greater = 大きい方から）並べて、
合計出現回数がkに等しくなった時点でその値を返す。

```cpp
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) : kth_(k), kth_largest_values_() {
        for (int num : nums) {
            add(num);
        }
    }

    int add(int val) {
        kth_largest_values_[val]++;

        int count = 0;
        for (auto it : kth_largest_values_) {
            count += it.second;
            if (count >= kth_) {
                return it.first;
            }
        }
        return -1;
    }

private:
    int kth_;
    std::map<int, int, std::greater<int>> kth_largest_values_;
};
```

- 参照：https://github.com/5103246/LeetCode_Arai60/pull/8/commits/47a331c2c1be203a67a24bb36b7d88833c60bc28 

- `greater` の仕様が priority queue と逆になっているように見えて頭がゴチャゴチャしたのだが、
priority queue がやっているのは優先順位を指定することであって並べ替えをすることではないことを理解すると腑に落ちた。
優先順位 = greater ということは top には一番小さいものがくる、だから昇順に見える、ということ？

- [コメント](https://github.com/5103246/LeetCode_Arai60/pull/8/commits/47a331c2c1be203a67a24bb36b7d88833c60bc28#r2327903392)より、
要素数がkを超えた部分を順次消していくと良いとのこと。これに沿ってさらに改良：
  ```cpp
  class KthLargest {
  public:
      KthLargest(int k, vector<int>& nums) : count_(0), kth_(k), kth_largest_scores_() {
          for (int num : nums) {
              add(num);
          }
      }
      
      int add(int val) {
          kth_largest_scores_[val]++;
          count_++;
          if (count_ > kth_) {
              auto it = kth_largest_scores_.begin();
              it->second--;
              count_--;
              if (it->second == 0) {
                  kth_largest_scores_.erase(it);
              }
          }
          return kth_largest_scores_.begin()->first;
      }
  private:
      int count_;
      int kth_;
      std::map<int, int> kth_largest_scores_;
  };
  ```

  - 各時点における全要素と出現回数の合計を持っておく。最も小さい値から評価していく。
  `count_++;` がkよりも大きい時、小さい方から余計な値を削っていく。小さい値を一つ削り、countも一つ減らす。
  最も小さい値の出現回数が0になったら、その時点でキーごと消す。最後に一番先頭の値を返す。

[multiset](https://cpprefjp.github.io/reference/set/multiset.html)を使うやり方。

```cpp
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) : kth_(k), kth_largest_scores_() {
        for (int num : nums) {
            add(num);
        }
    }

    int add(int val) {
        kth_largest_scores_.insert(val);
        if (kth_largest_scores_.size() > kth_) {
            kth_largest_scores_.erase(kth_largest_scores_.begin());
        }
        return *kth_largest_scores_.begin();
    }

private:
    int kth_;
    std::multiset<int> kth_largest_scores_;
};
```

- multisetは重複を許すset。mapを使う方法と似ている。

- デフォルトで`Compare == less`となっている。

問題設定から制約を考える。大学受験だとどんな感じ？

- 参照：[サイズについて1](https://github.com/Apo-Matchbox/LeetCode_Practice/pull/21#discussion_r2296674201)、[サイズについて2](https://github.com/maeken4/Arai60/pull/8#discussion_r2127436569)

constを使うかどうかについて。以下のコメントでは `int` が小さいデータ型なので使わなくて良いとしている。

- 参照：https://github.com/maeken4/Arai60/pull/8#discussion_r2127971544

struct と class。structは「"passive objects that carry data"にのみ用い，メンバ変数，メンバ関数は全てpublicでなければならず，従ってユーザーなどからアクセスされうるこれらに不変性などを仮定してはいけない」。

- 参照：https://ttsuki.github.io/styleguide/cppguide.ja.html#Structs_vs._Classes

より一般的なものとして map や multimap などを使う方を念頭におくべき？Step 3はmapを書いてみることにした。

- [データ構造の中身と実装](https://discord.com/channels/1084280443945353267/1183683738635346001/1185264362508795984)。「set, map, multiset, multimap の中身が平衡木で、多くのコンパイラ環境では赤黒木であること」が常識なら、map や multiset を使う方法が浮かんでくるのが自然か。

# Step 3

map を使って書いた。

- map の名付けがこれで良いのかは疑問が残る。値と登場回数を管理するカウンターという意味を込めて `counter` と名付けた。

Step 4 を作って他の選択肢の練習とか関連することをやってみようと思う。[heapの実装](https://github.com/irohafternoon/LeetCode/pull/10/commits/0601c01c5dce65b188109482efab34c039b294bd#r2024772173)とか？ちょうど前の問題につけてもらったレビューが見直せなくなっていたので。
