# 283. Move Zeroes

## Step 1

配列 `nums` の中の `0` を全て後ろへ移す。

- 制約：`1 <= nums.length <= 10^4, -2^31 <= nums[i] <= 2^31 - 1`
- その他の要素の要素の順序を変えては行けない。`nums` のコピーを作るのもダメ。

配列を左端から見ていって、0にぶつかったら後ろに移すやり方がありそう。でもインデックスがずれてしまいそう。移し方に気をつけるといいかも？例えば、0 の位置を溜めておいて、後からまとめて移す、というのは良いかも。でもこれでも難しい。ゼロの数を数えておいて、後から足すのではどう？これでも問題は変わらないか。

- この辺で15分、詰まったので解答を見る。

3つ目の「ゼロの数を数えておいて、後から足す」方法。

- 0を消すタイミングでインデックスを進めないのが重要。消すと次の要素が前にずれてくるので、前に来た要素を見るために `i` は増やしてはいけない。
- `count_zeros.cpp` に書いた。
- ただし、`erase` は毎回 $O(n)$ で、全部 0 の場合には $O(n^2)$ になってしまう。

まず 0 でない要素を前に詰めていく。詰め終わったら、配列の長さ分まで 0 を後ろに入れる。

- あくまでも「詰める」というのはイメージで、実際のところは書き換えをしている。
- `step1.cpp` に書いた。
- 同じイメージで `std::swap` を使うこともできる。`use_swap.cpp` に書いた。
  - こちらだと、先頭のゼロとゼロでない要素とを入れ替えていく感じ。`insert_pos` が現時点で出会った先頭のゼロの位置を表している（なので `pos_first_zero` でも良いかも）。

## Step 2

イテレータ操作による swap。`iter_swap()` というのを使う。

- [参照](https://github.com/potrue/leetcode/pull/54/changes)
- [レファレンス](https://cpprefjp.github.io/reference/iterator/iter_swap.html)

`std::remove()` を使った解法。

```cpp
#include <algorithm>
#include <vector>

class Solution {
public:
    void moveZeroes(std::vector<int>& nums) {
        // it - pos_last_nonzero? 
        auto it = std::remove(nums.begin(), nums.end(), 0);
        std::fill(it, nums.end(), 0);
    }
};
```

- c.f., [Erase-remove idiom](https://discord.com/channels/1084280443945353267/1210494002277908491/1211368894669787226)。
  - Step 1 で `erase` を使った際に自分が困っていたことがまさに出てきている
- `remove` を使って非ゼロを前に詰め、残りを `fill` で埋める。
- [`remove` は条件を満たさない要素を全て前に持ってくる](https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom) ので、こういうことができる。
  > These algorithms do not remove elements from the container, but move all elements that do not fit the removal criteria to the front of the range, keeping the relative order of the elements.
- `remove` された要素と同じ長さの要素が末尾に入る。
  > As no elements are actually removed and the container retains the same size, the tail of the array has a length equal to the number of "removed" items; these items remain in memory but in an unspecified state. remove returns an iterator pointing to the first of these tail elements so that they can be deleted using a single call to erase.

逆に nonzero 要素を数えるのでも良い。

- [参照](https://github.com/fhiyo/leetcode/pull/54/changes#:~:text=%2B-,%60%60%60py,-61)

Bubble sort に言及している人がそれなりにおり、前に見た [sorting algorithm animation](https://www.toptal.com/developers/sorting-algorithms) のことを思い出した。

みんな swap に行き着いているかも？

- [参照](https://github.com/hayashi-ay/leetcode/pull/58/changes)

## Step 3

swap を使うやつ、remove + fill、0を数えるやつ、どれもまあわかりやすさは同じくらいだった。時間にも差はない。

個人的には erase を使うのもわかりやすいと思ったんだが、erase によるシフトがあるのが良くない。
