# Step 1

## 1回目

### コード

141 の方針に沿いながら、訪問済みのノードにぶつかった際の動作を変えることで対応しようとした。

- `null` は `NULL` でなければならない。

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

- 普通に、ポインタを返せば良いことを理解した。ポインタを返すことはノードを返すことと同義。問題文には "Note that `pos` is not passed as a parameter" とあるが、その通り。Unordered set は index を持たない (c.f., hash tables)。

## 2回目

OK。

