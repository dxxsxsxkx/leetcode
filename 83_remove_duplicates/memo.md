# Step 1

## 1回目

### コード

141 / 142 の方針と似ているのではと思った。すでに見た値の set を作り、ポインタを動かしてそれぞれのノードの値が set に入っているかを判別していく方針を考えた。。

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        set<int> val_seen;
        ListNode* node_curr = head;

        while (node_curr != nullptr) {
            if (val_seen.contains()) {
                ListNode.remove(node_curr);
                return ListNode
            }

            val_seen.insert();
        }

        return ListNode
    }
};
```

### コメント

Yu Nakamura さんの解答（下記）を参照した。

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* curr = head;
        while (curr != nullptr && curr->next != nullptr) {
            if (curr->val == curr->next->val) {
                curr->next = curr->next->next;
            } else {
                curr = curr->next;
            }
        }
        return head;
    }
};
```

- `curr->val` という表現がよくわからなかった。`->` がメンバ変数の読み取りをする演算子（？）なのだということを理解すると、腑に落ちた。つまりここでは `curr` が指しているノードの値を読み取っている。`(*curr).val`も同じ。

- `remove` などを使っていないのが興味深いと思った。

    - 重複の削除は `curr->next = curr->next->next;` で行われている。これがやっているのは、`curr->next` という参照先（矢印として見るとわかりやすい）を `curr->next->next` に付け替えるという作業。

    - ここでいう「削除」とはリストのつながりから除外することであり、文字通りの削除ではない。

- `if ...` 構文の中でポインタを動かさないのは、連続して重複がある可能性に対処するため。

- `curr->next != nullptr` をチェックするのが必要。ループの中でアクセスしているので。

- "Return the linked list sorted as well." という要件が気になったが、確かにこの方法であれば順番は壊れなさそう。
