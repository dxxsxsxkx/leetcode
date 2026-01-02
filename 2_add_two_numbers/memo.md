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

# Step 2

特に変更点はない（再帰はまだよくわかってないのでこのまま書く）が、色々勉強する。

## 勉強

- メモリについて、[Yu Nakamuraさんのメモ](https://github.com/hemispherium/LeetCode_Arai60/pull/6/commits/c9b959e1bec5800dbdbf5e45bd20209fb7b6404c)より。
  ```cpp
  class Solution {
  public:
      ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
          ListNode sum(0);
          ListNode* curr = &sum;
          ListNode* num1 = l1;
          ListNode* num2 = l2;

          int carryOver = 0;
          while (num1 != nullptr || num2 != nullptr) {
              int sumOfTheDigits = 0;
              if (num1 != nullptr) sumOfTheDigits += num1->val;
              if (num2 != nullptr) sumOfTheDigits += num2->val;
              sumOfTheDigits += carryOver;
              curr->val = sumOfTheDigits % 10;
              carryOver = sumOfTheDigits / 10;
              ListNode temp(0);
              curr->next = &temp;
              curr = curr->next;
              if (num1 != nullptr) num1 = num1->next;
              if (num2 != nullptr) num2 = num2->next;
          }
          return &sum;
      }
  };
  ```

  - `temp` は stack 上に保存されており、`while`のループが終わるたびに破棄される。そのため、`return &sum` で `curr` が次に指している `temp` のアドレスを参照しようとしてもうまくいかない（存在しないオブジェクトを指してしまう）。これが `ListNode new ...` を使って heap 上にノードを作成する必要がある理由。

- [gt32さんのアプローチ](https://github.com/5103246/LeetCode_Arai60/pull/5/commits/475690037f777b12e6f01dfd3335fd7c2fbcb5db)：「2つのリストを2つの数字に変換してから合計値を求め、合計値をリストにする方法」。「unsigned long long型の範囲を超える場合を考慮してなかったので、桁数が大きい時にエラーになった」ということらしい。どういうことか？

  - `unsigned long long` は64ビット整数で、最大値は $2^64 - 1 ≈ 1.8 × 10^19$、すなわち10進数で20桁が表現できる限界。これよりも大きい数字が出てきてしまうと扱えなくなるということ。で、問題の制約を見るとノード数の最大が100なので、全然足りなくなりうる。

  - 具体的に何が起こるのか？：unsigned 整数の演算は常に $2^n$ を法とする演算になっており、そこに達すると数値が0に巻き戻る（defined behavior; c.f., undefined behavior）。

- [再帰バージョン](https://github.com/5103246/LeetCode_Arai60/pull/5/commits/475690037f777b12e6f01dfd3335fd7c2fbcb5db)。ヘルパー関数を呼び出す以外はやっていることは同じ。2パターンの使い分けについて考えたい。
  ```cpp
  class Solution {
  public:
      ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
          return addTwoNumbersHelper(l1, l2, 0);
      }

  private:
      ListNode* addTwoNumbersHelper(ListNode* l1, ListNode* l2, int carry) {
          if (!l1 && !l2 && !carry) return nullptr;

          int sum = carry;
          if (l1) {
              sum += l1->val;
              l1 = l1->next;
          }
          if (l2) {
              sum += l2->val;
              l2 = l2->next;
          }
          ListNode* node = new ListNode(sum % 10);
          node->next = addTwoNumbersHelper(l1, l2, sum / 10);
          return node;
      }
  };
  ```

  - [このコメント](https://github.com/fhiyo/leetcode/pull/5/files)より。リストの最大サイズに鑑みると再帰が深すぎることはなく、stack overflow の心配はなさそうだと判断している。8MB のスタックがあって1回の関数呼び出しで 48 バイト使うなら約17万回の再帰が理論上可能、という計算（実際はもっとかかるっぽいが、それでも問題はなさそう）。

    > スタックサイズ8MBとして、スタックフレーム辺りの引数、ローカル変数でポインタ3つ、intが2つ + ベースポインタとリターンアドレスで48byte+αくらいだろう?>か？とすると 8*2**20/48 ≒ 170K回くらいは深くできそう。(ポインタやレジスタのサイズを64bitとして計算している)

- ダミーの初期化について、[この議論](https://github.com/fhiyo/leetcode/pull/5/files#r1594033534)を見た。難しいので LLM に解説してもらう。

    - 問題：`ListNode dummy;` と書いたときに、メンバは安全に初期化されるのか？
    C++ では初期化方法・型の性質・言語バージョンによって挙動が変わるが、複雑さを避けるためにvalue-initialization（例：{}）を使うのが最も安全になる（最後の[fhiyoさんのコメント](https://github.com/fhiyo/leetcode/pull/5/files#r1602779649)）。

    - POD: plain old data

    - `dummy(-1000)`のような書き方は direct initialization / user-defined constructorか。

- [メモリリーク問題](https://github.com/jiku0730/LeetCode/pull/11#discussion_r2146798981)。