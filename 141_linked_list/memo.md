# Step 1

## 1回目

### コード

書けなかった。

### コメント

- pos は passed by value

- pos が head の要素であるかどうかを判定すれば良い

- exception: 
  - pos が head の外にあるケース

### 感想

- そもそも linked list という型が何かを理解していないので、的外れなことを書いている。

## 2回目

### コード

ChatGPTに提案された「ウサギと亀」アルゴリズムで解いた。

```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        
        // Does the list have at least two elements? 
        if (head == nullptr || head -> next == nullptr) {
            return false;
        }

        // Use two pointers, fast and slow
        ListNode fast;  // two at a time
        ListNode slow;  // one at a time

        // As long as the fast pointer has not hit the end
        while (fast != nullptr && fast -> next != nullptr) {
            // If two pointers meet each other
            if (fast == slow) {
                return true
            }

            slow -> next
            fast -> next -> next
        }
    }
}
```

### 感想

- `ListNode*` の * が抜けている。ノードとポインタの区別がついていない。`ListNode` ではノードを指してしまう。

- fast と slow が初期化されていない。C++ ではオブジェクトの初期化は自動的には行われない。

- ループの中で fast と slow の代入処理が行われていない。

- セミコロンが抜けている。

- 関数のデフォルト戻り値がない。

## 3回目

### コード

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        
        // Does the list have at least two nodes? 
        if (head == nullptr || head -> next == nullptr) {
            return false;
        }

        // Define two pointers (fast / slow)
        ListNode* fast = head -> next -> next; // two at a time
        ListNode* slow = head -> next; // one at a time

        // If the two pointers meet each other
        while (fast != nullptr && fast -> next != nullptr) {
            if (fast == slow) {
                return true;
            }

            // Move pointers
            fast = fast -> next -> next;
            slow = fast -> next;
        }

        return false;
    }
};
```

### 感想

- `slow` が `fast` を基準に動いてしまっている。書き間違い。

### 4回目

OK。

### コード

`step1.cpp` に記載。

# Step 2

### 修正点

- コメントを追加した

### 勉強

Linked list について

- ノードは前後のノードへの参照情報を持っている

解法について

- ウサギと亀は重要ではなく、set を使った解法で書けるかどうかが重要。`step2.cpp`にはこちらを書く。
    - 全探索ではなく、1つのポインタのみを使う方法。
        ```python
        class Solution:
        def hasCycle(self, head: Optional[ListNode]) -> bool:
            seen = set()
            current = head

            # 既に見た要素に当たったら循環があることになる
            while current:
                if current in seen:
                    return True
                seen.add(current)
                current = current.next

            return False
        ```

        ```cpp
        class Solution {
        public:
            bool hasCycle(ListNode *head) {
                set<ListNode*> visited;
                ListNode* curr = head;  // curr = current

                while (curr != nullptr) {
                    /*
                    NOTE: visited.find() doesn't work because it returns an iterator
                    On the other hand, visited.count returns 1 if the set contains the specified element
                    */
                    if (visited.count(curr)) {
                        return true;
                    }
                    visited.insert(curr);
                    curr = curr->next;
                }

                return false;
            }
        };
        ```

    - [Odaさんのコメント](https://discord.com/channels/1084280443945353267/1195700948786491403/1196021630103724134)。Campbell's law or Goodhart's law. 知っていることはすごくも当たり前でもない。

- 遅いポインタのみで全探索する場合、リストの長さを n としたときに空間計算量が O(n) になり、メモリを食う。ウサギと亀を使うと空間計算量が O(1) になる。
    - [tk-hiromさんの解法](https://github.com/tk-hirom/Arai60/pull/1/commits/967ba6e39e0f6fd44a044778596f7dcd13ad0160)。コメントは自分で付記した。
        ```python
        class Solution:
        def hasCycle(self, head: Optional[ListNode]) -> bool:
            # リストの要素を一つ一つチェックする
            checkedElements = []
            target = head
            if not target:
                return False

            # target を動かしていく
            # 既にチェックした要素に当たったら、循環があることになる
            # 上の方法とは逆になっている
            while(target not in checkedElements):
                checkedElements.append(target)
                if not target.next:
                    return False
                target = target.next
            return True
        ```

- もっとシンプルな書き方？

    - [hardjuiceさんの解法](https://discord.com/channels/1084280443945353267/1195700948786491403/1196021630103724134)。
        ```python
        class Solution:
        def hasCycle(self, head: Optional[ListNode]) -> bool:
            node_set = set()
            curr_node = head
            while curr_node:
                if curr_node in node_set:
                    return True
                node_set.add(curr_node)
                curr_node = curr_node.next
            return False
        ```

その他

- [Odaさんのコメンt](https://github.com/hemispherium/LeetCode_Arai60/pull/2/files/c519479ca1ba60ab36c8cdf5be00fd06b352d7e9)。
`head == nullptr`を確認するのには良し悪しがあるとのこと。

  - 動作が変わる点：入力によってはループまで行っていたものがその手前で弾かれるようになる。

- [Odaさんのコメント](https://github.com/tk-hirom/Arai60/pull/1)。
List の要素を in を使って確認する場合、要素数に線形で比例してかかる時間が増える。

- 他の人のコードを見ていると、自分のコメントは冗長すぎるかもしれないと思う。