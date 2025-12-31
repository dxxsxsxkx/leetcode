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

# Step 2

色々他にもやり方はあるが、前提条件を踏まえるとシンプルな step 1 の方法を使うことにした。

## 勉強

[新しく list を構築する方法] (https://github.com/hemispherium/LeetCode_Arai60/pull/4/files/89a3705df5a7faf6dc3665d30587c0c9582da512#r2605619330) がある。

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        
        ListNode* node_curr = head;

        // Define a new list
        ListNode dummy(0);
        ListNode* tail = &dummy;

        // 次の val とは違う val を新しいリストに追加していく
        while (node_curr != nullptr) {
            if (node_curr->next == nullptr || 
                node_curr->val != node_curr->next->val) {
                tail->next = new ListNode(node_curr->val);
                tail = tail->next;
            }
            node_curr = node_curr->next;
        }

        return dummy.next;

    }
};
```

- `ListNode dummy(0)` はスタック上にノードを一つ作る。0は意味を持たず、リストの先頭は `dummy.next` になる。ダミーがないと、以下のように `if ... else` を使うことになり、複雑になる。
    ```cpp
    if (list is empty) {
        head = new ListNode(...);
    } else {
        tail->next = new ListNode(...);
    }
    ```

- `while` 内はこっちの方がいいかも↓：
    ```cpp
    while (curr != nullptr) {
        if (curr->next != nullptr &&
            curr->val == curr->next->val) {
            curr = curr->next;
            continue;
        }

        tail->next = new ListNode(curr->val);
        tail = tail->next;
        curr = curr->next;
    }
    ```

- 隣同士を比較しているので、sorted list ではない場合には対応できない。unordered set を使ったりすると対応できる（一度見た val を set に追加していく + val が set に含まれているかどうかで条件分岐を入れる）。
  
[二重ループ版](https://github.com/hemispherium/LeetCode_Arai60/pull/4/files/89a3705df5a7faf6dc3665d30587c0c9582da512#r2605744764)もある。

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* curr = head;

        while (curr != nullptr) {
            ListNode* runner = curr;
            while (runner->next != nullptr && 
                   // ここが面白い；head との比較をする
                   runner->next->val == curr->val) {
                runner->next = runner->next->next;
            }
            curr = curr->next;
        }
        return head;
    }
};
```

- どちらかというと、two pointer 版といった方がわかりやすい？`head`は固定した上で、もう一個の pointer （`runner`）を「走らせ」て重複を探す。重複の探索を `head` を基準にやるか `runner` を基準にやるかが違う。

- list がソートされていない場合のために、`runner` vs. `head` をやっている。

# Step 3

問題なくできた。