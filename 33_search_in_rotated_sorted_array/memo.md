# 33. Search in Rotated Sorted Array

## Step 1

二分探索で解こうと考える。

- 前回とは違って `k < nums.length` なので元の配列に戻ることはないのでは？配列の値がユニークであることと合わせて、狭義単調増加が二つ並ぶ形になる。
- `target` が存在する範囲を絞っていく。
- 不変条件をどう設定すれば良いか、今ひとつ当たりがつかない。とりあえず閉区間を使ってみることにする。つまり、`[left, right]` に `target` が入る状態を保つ。
- 中点の設定は `mid = left + (right - left) / 2` と切り捨てにする。
- どう範囲を縮めていけば良いだろうか？
  - 部分配列が切り替わるところに崖があるようなイメージを持つ。もとの配列の最後の値と中点の値を比べると崖の位置が左右どちら側の配列にあるかが分かる。
  - ただもう一個比較が必要な気がする...。中点の値と `target` を比べる？この辺で噛み合わなくなったので答えを見る。ここまで30分。

答えを見る。`step1.cpp` に書いた。

- 崖がどちら側にあるかが分かれば、逆側の部分配列が狭義単調増加になることが分かる。
- この狭義単調増加列の中に `target` が入るかを確認する。含まれればその配列を残す。含まれなければ逆側を残す。
- 一番外側の等号は部分配列が一つだけ残ったケースのため、内側の等号は `left` と `target` ないしは `target` と `right` が一致した場合のために必要。

元々考えていた崖の位置の判定は、崖の位置が左右どちらにあるかというよりは `mid` と `target` がどの区間に属しているかを判定していると考えた方が良い。これは `step1_alt.cpp` に書いた。

- Left-rotation の結果として左側に置かれた値は全て `nums.back()` より大きく、そうでない値は全て小さい。このことを利用して、`mid` と `target` がどちら側の部分配列にあるかを知ることができる。
- 両方が同じ側の部分配列に属していればその中で通常の二分探索をすれば良い。そうでない場合は `target` が存在する側の部分配列で二分探索をすれば良い。

## Step 2

2回二分探索する方がわかりやすい...。好みなのかしら。

### 勉強

一回最小値を見つけてから二分探索をやる方法がある。
> 一つ前の問題でrotateされたソート済みリストの最小値を見つける問題があるので、それを応用して解く。最小値の位置がrotate前の位置からどのくらいずれているかのoffsetを計算して、ズレを修正しながら二分探索すればいい。

- ふむ。言いたいことはわかった。
- 書いてみた（`use_min.cpp`）けど、配列が頭の中で混ざってややこしいかも...。
- [参照](https://github.com/fhiyo/leetcode/pull/44/changes)

`std::partition_point()` を使う方法。

```cpp
class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        auto it = std::partition_point(nums.begin(), nums.end(), [&nums, target](int x){
            return (target >= nums.front() && (x >= nums.front() && x < target)) ||
                   (target < nums.front() && (x >= nums.front() || x < target));
        });
        if (it != nums.end() && *it == target) {
            return std::distance(nums.begin(), it);
        }
        return -1;
    }
};
```

- [参照](https://github.com/potrue/leetcode/pull/43/changes)
- `pred(x)` が `true` になる最後の位置の次（= 最初の `false` の位置）を返す。
- うーんまだしっくりきていないかも。`pred(x)` の作り方のところが微妙。
  - 渡された配列は `nums.front()` 以上の部分とそれよりも小さい部分に分かれる。どちらの部分に target が属するかによって操作を変える。
  - 結局、`target` より前に来る要素が全て `false` になるのだが、そういう風に天下りで考えているのか...？
- 場合分けして考えたらちょっとわかったかも。
  1. 場合1：`target` が `front` 以上（左ブロック）→ x も左ブロック内なら通常比較 → 右ブロックは全部 `target` より後ろ扱い
  2. 場合2：`target` が右ブロック → 左ブロックは全部 `target` より前扱い → 右ブロック内では通常比較

うーん...？
> 二分探索を行うにあたり、条件式が left <= right となることは通常ないように思います。区間の考え方が曖昧なように感じます。区間は「閉区間」「半開区間」「開区間」のどれで考えていますか？
> 仮に閉区間で考えているとすると、最終的には区間内に要素が一つだけ残るようにすると思います。その場合、 left == right となったタイミングでループが終わると思います。すると、条件式は left < right となると思います。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/47/changes#r1874209355)
- 問題の捉え方が違うのか？
  - [考え方の手順...](https://github.com/Ryotaro25/leetcode_first60/pull/47/changes#r1874210398)
- 「仮に閉区間で考えているとすると、最終的には区間内に要素が一つだけ残るようにすると思います」のところがわからないかも。

`bisect_left` の方法はちょっと余裕ないのでまた今度

- [参照](https://github.com/fhiyo/leetcode/pull/44/changes)

## Step 3

2回二分探索で書いた。
