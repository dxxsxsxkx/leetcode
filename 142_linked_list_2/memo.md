# Step 1

## 1回目

### コード

141 の方針に沿いながら、訪問済みのノードにぶつかった際の動作を変えることで対応しようとした。

- `null` は `NULL` でなければならない → 現在は `nullptr` を使う。型を判別しやすくするための方法で、C++11 から導入されたそう。

- `visited.find()` を使えるような気がしたが、ダメだった。

```cpp
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr | head->next == nullptr) {
            return null;
        }

        set<ListNode*> visited;
        ListNode* node_curr = head;

        while(node_curr != nullptr) {
            if (visited.count(node_curr)) {
                // find the index
                int pos_connected = visited.find(node_curr);

                return visited[node_curr];
            }

            visited.insert(node_curr);
            node_curr = node_curr->next
        }

        return null;
    }
};
```

### コメント

- `return NULL` ではなく `break` で良い。

- 普通に、ポインタを返せば良いことを理解した。ポインタを返すことはノードを返すことと同義。問題文には "Note that `pos` is not passed as a parameter" とあるが、その通り。Set は index を持たない (c.f., hash tables)。

## 2回目

OK。

# Step 2

## 勉強

- ウサギと亀を使った解法もある。この場合、141 のように cycle を検出した後に slow pointer を出発点に戻すと衝突点が結節点と一致する。
    ```cpp
    class Solution {
    public:
        ListNode *detectCycle(ListNode *head) {
            if (!head || !head->next) return nullptr;

            ListNode* slow = head;
            ListNode* fast = head;

            // Phase 1: detect cycle
            while (fast && fast->next) {
                slow = slow->next;
                fast = fast->next->next;
                if (slow == fast) break;
            }

            if (!fast || !fast->next) return nullptr;

            // Phase 2: find entry
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }

            return slow;
        }
    };
    ```

- [`contains`](https://en.cppreference.com/w/cpp/container/set/contains.html) を使う方法があるらしい。使うと↓のようになる。`count` より意味が直観的になるように思う。
    ```cpp
    if (visited.contains(node_curr)) {
        return node_curr;
    }
    ```

    - ちなみに `contains` の計算量は O(log(N)) とのこと。ChatGPT に聞くと、赤黒木を使うことで最悪計算量を抑えているらしい。

# Step 3

問題なくクリア。

## メモ

- `unordered set` を使っても問題なく通ることを確認した。`set` と違って最悪計算量が大きい。