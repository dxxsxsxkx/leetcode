# Step 1
 
## 1回目

### コード

二つポインタを作り、片方を `node_curr`、もう片方を `runner` として走らせて重複を検知した上で、最後に `node_curr` 自体も消してしまおうとした。うまく行かなかった。

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* node_curr = head;

        while (node_curr != nullptr && node_curr->next != nullptr) {
            if (node_curr->val == node_curr->next->val) {
                // Use runner
                ListNode* runner = node_curr;

                // NOTE: この比較はおかしい
                while (runner->val == runner->next->val) {
                    // Move the runner first?
                    runner = runner->next;
                    node_curr->next = node_curr->next->next;
                }

                node_curr = node_curr->next;
            }
            
        }

        return head;
    }
};
```
### メモ

- `runner`を使うのであれば `if (node_curr->val ...)` の比較は必要ない。

- 初手で頭にアイデアが浮かんだので、紙にステップを書いて考えてみた。できなかったが、頭は整理される。
自然言語でやりたいことをちゃんと整理すると、上のコードの変な点が思い浮かぶ。

  - たとえば、「`runner` と比較するべきなのは何？」など。

- 気になったので上のコードからさらに考えて `is_dup_curr` というフラッグを作って扱おうとした。方針としては良さそうだが、別の点でうまくいかない。
ここで諦めて解答を見る。

  ```cpp
  class Solution {
  public:
      ListNode* deleteDuplicates(ListNode* head) {
          ListNode* node_curr = head;
          bool is_dup_curr = false;

          while (head != nullptr) {
              node_curr = head;
              while(node_curr != nullptr) {
                  ListNode* runner = node_curr;
                  is_dup_curr = false;  // re-initialize

                  if (runner->next != nullptr &&
                      runner->next->val == node_curr->val) {
                          runner->next = runner->next->next;

                          // flag
                          is_dup_curr = true;
                      }
                  
                  node_curr = node_curr->next;
              }

              if (is_dup_curr == true) {
                  head = head->next;
              }
          }

          return head;
      }
  };
  ```

- 最終的に、dummy node を使うという発想がなかったことがわかった。

## 2回目

コードは step1.cpp に書いた。

### メモ

- `ListNode* prev = &dummy` によって `prev` に加えられた変更が `dummy` にも加えられ続ける（アドレス参照）？

- 色々な input を使って 1ステップごとに考えてみた。変数の名付けに自分の認知が釣られていることがよくわかった。

- `node_curr`が前に進んでも、前の `node_curr->next`はちゃんと残る？各回の if ... else の中の `node_curr->next = runner;` の処理結果は、次の if ... else にもそのまま保持されているということ？

  - `node_curr` はポインタであってノードそのものではない。`node_curr->next`は「`node_curr`が指していたノードの`next`」を表している。
  こう考えるとしっくりくるが...。

  - とりあえず、こういう風な理解に到達した後はスラスラと書けた。

# Step 2

## コード

最終形を step2.cpp に書いた。

## 勉強

- [他の人のコード](https://github.com/hemispherium/LeetCode_Arai60/pull/5/commits/a1e0bb0ed12ad3b03421cb10309fa8a8246d5e99)で `dummy(-1000)`を使っているのを見かけた。`-100 <= Node.val <= 100` という制約から外れるようにしているのだと理解した (参照：[このコメント](https://github.com/5103246/LeetCode_Arai60/pull/4/commits/a5301e9db863d53d1d6c4e9925cff2917555e970#r2287948164))。

- [このコメント](https://github.com/5103246/LeetCode_Arai60/pull/4/commits/a5301e9db863d53d1d6c4e9925cff2917555e970#r2286491895)を見る。重複のあるノードを飛ばした後にそのノードのために使用していたメモリを解放するという作業が存在することがわかった。ノードは heap に置かれているので、ちゃんと削除してあげると良い。

  - [ここ](https://discord.com/channels/1084280443945353267/1366778718705553520/1377689037208289471)でいうデザインの話なのか？

  - `delete` を使ってみる。

- 名付けの問題が色々指摘されている。

  - [Google Style Guide](https://google.github.io/styleguide/cppguide.html#General_Naming_Rules)より。`node_curr`は`node_current`として良いかも。同様に `val` → `val_duplicate`。

- ネストが深すぎるかも？たとえば次のコードと比べてどちらが見やすいだろうか。ただ、判断がつかないのでとりあえずはこのまま。
  ```cpp
  class Solution {
  public:
      ListNode* deleteDuplicates(ListNode* head) {
          ListNode dummy;
          dummy.next = head;

          ListNode* prev = &dummy;
          ListNode* curr = head;
          while (curr) {
              while (curr->next && curr->val == curr->next->val) {
                  curr = curr->next;
              }

              if (prev->next != curr) {
                  prev->next = curr->next;
              } else {
                  prev = curr;
              }

              curr = curr->next;
          }

          return dummy.next;
      }
  };
  ```

# Step 3

スムーズに書けた。