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
