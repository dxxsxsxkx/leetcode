# 35. Search Insert Position

## Step 1

時間計算量 $O(N \log N)$ の制約があるので二分探索でやることが求められているんだろう。`step1.cpp` に書いた。

- 時間計算量は $O(\log N)$、空間計算量は$O(1)$。
- 制約：`1 <= nums.length <= 10^4`、`-10^4 <= nums[i] <= 10^4`、`-10^4 <= target <= 10^4`。
- 探索区間が毎回半分になっていき、かつ比較を入れているので片方のみ再帰が入る。1ステップの計算量は $O(1)$、ステップ数は何回2で割ると1になるかを計算するので、$N / 2^k = 1$、よって $k = \log_2 N$。
- 実行時間：1ステップにつき5回、配列サイズは最大で `10^4` なので $5 \times \log_2 10^4 / 10^8 \approx 10^{-6}$sくらい。

再帰しないバージョンも書いてみる。こちらの方が返り値のアドレス確保やレジスタ退避がないのでちょっと早い。

```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int begin = 0;
        int end = nums.size();

        while (begin < end) {
            int mid = begin + (end - begin) / 2;
            if (target <= nums[mid]) {
                end = mid;
            } else {
                begin = mid + 1;
            }
        }

        return begin;
    }
};
```

## Step 2

### 勉強

[参照](https://github.com/potrue/leetcode/pull/41/changes#r2264622846)：ちゃんと分かってないかも...。

> 1. 区間には何が含まれますか？
> 2. left が指す対象は何ですか？
> 3. right が指す対象は何ですか？
> 4. ループの不変条件 (left < right) を決めるとき、どのように決めましたか？
> 5. int mid = (left + right) / 2; のほうがシンプルですが、なぜ int mid = left + (right - left) / 2; なのですか？
> 6. left = mid + 1; の + 1 の部分は、なぜ + 1 なのですか？ - 1 や 0 でないのはなぜですか？
> 7. right = mid; にはなぜ - 1 や + 1 を付けていないのですか？
> 8. なぜ left を return しているのですか？

- 5.の選択肢は考えなかった。足し算をすると `left` や `right` が非常に大きい場合にオーバーフローが起こる。
- 6.について、2で割ったときの切り捨ての操作の話はわかっていなかった。
- [c.f., 問い](https://discord.com/channels/1084280443945353267/1196498607977799853/1269532028819476562)
- [c.f., 読み方](https://github.com/philip82148/leetcode-swejp/pull/13#discussion_r2043982312)。読むのが大事なアルゴリズム。

[参照](https://github.com/5103246/LeetCode_Arai60/pull/39/changes#r2819143481)：空リストに対して何を返すかだが、「数式上の振る舞いが整っている方が後々都合がいいことが多い」というのは納得。空リストに新しく要素を挿入するのであれば `0` を返すのが自然か。

[参照](https://github.com/5103246/LeetCode_Arai60/pull/39/changes#r2819131634)：区間の分け方を変えても良いかも？

ちょっと整理して書いてみた。以下のコードだと、1. の問題定義と return のロジックが一致していない。例えば　`[1, 3, 3, 3, 5], target = 3` のようなケースでは左の 3 を返すべきところ、このコードでは真ん中を返してしまう。

```cpp
#include <vector>
class Solution {
public:
    // 1. [false, false, false, ..., true, true, true] となる列において、
    //  一番最初の true となるインデックスを返す問題だと考える
    // 2. 答えが含まれる範囲を狭めていって、最後に残ったインデックスを返す
    int searchInsert(std::vector<int>& nums, int target) {
        // 8. エッジケース：空リスト
        if (nums.empty()) {
            return 0;
        }

        // 3. 最初は 0 から nums.size() - 1 までを考える
        int begin = 0; 
        int end = nums.size() - 1;

        // 4. 最後に残ったインデックスを判定する際には、begin <= end を使う
        //  - `begin > end` になった場合には終了
        while (begin <= end) {
            // 5. 半分に切っていって、中間点がどちらの区間に入るかで考慮する区間を絞る
            //  - 常に [begin, end] の区間が答えがある区間と一致するようにする
            //  - integer overflow に注意
            int mid = begin + (end - begin) / 2;

            // 6. `target` が mid に対してどの位置にあるかで絞り込み
            if (target == nums[mid]) {  // 被ったらそれを返す
                return mid;
            } else if (target < nums[mid]) {
                end = mid - 1; 
            } else {
                begin = mid + 1;
            }
        }

        // 7. 最後はどっちでも良い
        return begin;
    }
};
```

- 一致させるためには即座に return せず限界まで範囲を絞っていくべき。この考え方で `step2.cpp` に書いた。
- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/45/changes#r1887753088)。「最終的な挙動からボトムアップに思考しているように見え、違和感を感じました。二分探索の問題のモデルからトップダウンに考えていき、その内容を記述するのが良いと思います」というコメントに納得。他の問題でも問題のモデルが思いつかないケースがあるなと思った...。

他のモデルも考えてみるか。

- 区間の作り方：半閉区間の境界のどちらを閉じるかで `target, nums[mid]` の比較の方法が変わる。
- 初期値：これも区間の作り方で決まる？右が開いた半閉区間を考えるためにこういう設定にしているのであって、例えば `[begin, end]` や `(begin, end)` を考えるのであれば変える必要がある。

## Step 3

色々な組み方で練習してみる。`step3.cpp` には開区間で絞っていくやり方（i.e., 不変条件は `target` が `[begin, end]` に入る）で書いた。
