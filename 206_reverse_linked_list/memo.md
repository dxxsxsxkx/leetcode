# Step 1

## 1回目

### コード

stack を使う方法を思いついた。まず、リストの左から右まで stack に積んでいく。
その後、stack が空になるまで、新しいリストのポインタを stack の一番上の要素に繋げてからその要素を `pop` するのを繰り返す。

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        stack<ListNode*> st; 
        ListNode dummy(0); 
        ListNode* node = head; 
        ListNode* new_list = &dummy;

        while (node) {
            st.push(node);
            node = node->next;
        }

        while (!st.empty()) {
            new_list->next = st.top();
            st.pop();
            new_list = new_list->next;
        }

        return dummy.next;
    }
};
```

### メモ

- エラーが出た。`heap-use-after-free`、すなわち開放したメモリの領域にアクセスしたことによるエラー。
`new_list` の末尾のノードがどのノードにも繋がっていない状態で放置されたことが原因。
ChatGPT に聞くと、LeetCode 側が返ってきたリストを delete する際に、`head->next` をすでに delete されたノードとして参照しているとのこと。
`new_list->next = nullptr;` を `return dummy.next` の前に入れると問題なく通った。

  ```cpp
  Line 72: Char 9:===================================================================22==ERROR: AddressSanitizer: heap-use-after-free on address 0x502000000078 at pc 0x55b07efa8896 bp 0x7ffc94d525e0 sp 0x7ffc94d525d8
  ```

## 2回目

### コード

`step1.cpp` に記載。問題なく書けた。

# Step 2

## 勉強

- [Step 1 の問題について](https://github.com/maeken4/Arai60/pull/7#discussion_r2118169281)。循環参照になる？

- `head` は passed by value なので、そのまま操作することも一応可能。が、わかりづらくなる（動いたら `head` ではない）。

- [このコメント](https://github.com/5103246/LeetCode_Arai60/pull/7#discussion_r2312163656)にあるが、`reversed_list` は `reversed_list_head` とした方がわかりやすそう。

  - [名付け](https://discord.com/channels/1084280443945353267/1295357747545505833/1298524551592018003)。`node` も `original_head` にする。

- [再帰で書く方法]。
  ```cpp
  public:
    ListNode* reverseList(ListNode* head) {
        return reverseRecursively(head);
    }
  private:
    // node以降のリストを逆順に繋ぎなおし、元々の最後尾を新たなheadとして返す
    ListNode* reverseRecursively(ListNode* node) {
        if (node == nullptr || node->next == nullptr) {
            return node;
        }
        ListNode* head = reverseRecursively(node->next);
        node->next->next = node;  // ひっくり返す
        node->next = nullptr;  // 循環を切る
        return head;
    }
  ```

  - 他にもこういう方法も。片方をひっくり返して次に繋げる。
  ```cpp
    // [1,2,3], [4,5,6] -> [3,2,1,4,5,6]
    // [], [4,5,6] -> [4,5,6]
    ListNode* reverse_and_append(ListNode* head1, ListNode* head2){
        if (head1 == nullptr) {
            return head2;
        }
        auto new_head1 = head1->next;
        head1->next = head2;
        return reverse_and_append(new_head1, head1);
    }
  ```

- [考え方](https://github.com/irohafternoon/LeetCode/pull/9#discussion_r2020110286)。3種類ある。自分がやったのは3つ目だが、他にも「左から矢印を逆向きにする」「先頭の前に置いたダミーに向かって矢印をつける」がある。

# Step 3

問題なく書けた。

# Step 4

「左から矢印を逆向きにする」やつをやってみる（[参照](https://github.com/dxxsxsxkx/leetcode/pull/7#discussion_r2660820656)）。
まずあらかじめに、ひっくり返した先の終点（null）を参照するポインタを作る。
次に、リストを左から走査してポインタをひっくり返していく。
この時、あらかじめ次の参照先を取得しておくのが重要（現在のノードの参照先は更新されてしまうので）。


```cpp
/**
 * Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode() : val(0), next(nullptr) {}
*     ListNode(int x) : val(x), next(nullptr) {}
*     ListNode(int x, ListNode *next) : val(x), next(next) {}
* };
*/
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* reversed = nullptr; 
        ListNode* current = head; 
        ListNode* next_node = nullptr; 

        while (current) {
            next_node = current->next; 
            current->next = reversed; 
            reversed = current; 
            current = next_node; 
        }

        return reversed; 
    }
};
```
