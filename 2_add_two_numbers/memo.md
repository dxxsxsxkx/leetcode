# Step 1

## 1回目

### コード

82 と同じようなアプローチ。ダミーノードと2つのランナーを作り、それぞれの数字を追いかけて足し算をしてもらおうとした。

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(-1000); 
        dummy.next = l1;

        ListNode* node_current = &dummy;
        ListNode* runner1 = l1; 
        ListNode* runner2 = l2;

        while (runner1 != nullptr || runner2 != nullptr) {
            bool is_carried = false;
            int sum = 0; 
            
            if (runner1 != nullptr) sum += runner1->val; 
            if (runner2 != nullptr) sum += runner2->val;
            sum += is_carried;
            int first_digit = sum % 10;

            //std::cout << sum << std::endl;
            //std::cout << first_digit << std::endl;

            // carry-up
            if (sum >= 10) is_carried = true;

            node_current->next->val = first_digit; 

            // update runners
            if (runner1 != nullptr) runner1 = runner1->next;
            if (runner2 != nullptr) runner2 = runner2->next;
        }

        return dummy.next;
    }
};
```

### メモ

問題点。

- 繰り上がりがループを挟んで保持されていない。初期化の位置を変える。

- 繰り上がりは `bool` ではなく `int` にした方がわかりやすそう。

- ループの最後に繰り上がりが残るケースに対応できない。`while`の条件に繰り上がりが0ではないことを入れる。

　　- この点を考えると、返すリストは新しく作った方がわかりやすい。

- `node_current->next->val = first_digit;` で、`node_current->next`が必ず存在する保証がない。
`ListNode new ...` を使って新しく作る。

- 現在のノードの情報のみを使うので、ランナーは必要ない。

## 2回目

### コード

`step1.cpp` に記載。うまくいった。
