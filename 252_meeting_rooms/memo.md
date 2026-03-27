# 252. Meeting Rooms

## Step 1

ミーティングのスケジュールが衝突せずに入るかどうかを判定する。

- 制約：`0 <= intervals.length <= 500, 0 <= intervals[i].start < intervals[i].end <= 10^7`
  - 特にソートはされていない

一個でも衝突があれば `true` を返す。衝突のパターンは4つある。ナイーブに考えるとこれで全てのペアを判定していけば良いか。

- 最初は衝突する条件を書き出そうとしていたが、衝突のパターンはもう少しシンプルに書ける。衝突しないパターンから考えれば良い。これで `step1.cpp` を書いた。
- 時間計算量 $O(n^2)$, 空間計算量 $O(1)$

開始時刻でソートしてあげると速くなるか。隣同士だけを比較すれば良くなる。`sorted.cpp` に書いた。

- 最初、ループを `for (int i = 0; i < intervals.size(); ++i) {}` と書いたら `intervals = []` のケースで runtime error になった。unsigned integer がアンダーフローしてしまっている。
- 事務方の人のところにバラバラに予約が提出されるので、それを手元で順番に並べて判定する感じ。

## Step 2

先に `pair` にしてからソートしている。

```cpp
vector<pair<int, bool>> points;
for (vector<int>& interval : intervals) {
    points.emplace_back(interval[0], true);
    points.emplace_back(interval[1], false);
}
sort(points.begin(), points.end());
```

- [参照](https://github.com/potrue/leetcode/pull/55/changes)
- あ、これは LeetCode では Interval class を作っていないからか。理解。

会議室の鍵か。思いつかなかった。`keys.cpp` に書いた。
> 鍵を借りる時間と返す時間をばらばらにソートして、鍵の数が2つ以上でたかを確認という手もありますね。

- [参照1](https://github.com/Yoshiki-Iwasa/Arai60/pull/60/changes/9a196986631d3f52dad6e7ea577adb64204af31e#diff-7e5d8cbda3fd172d8f65764fe82e6ce4fe0ddef03db2dd8e8569cc620967d8b0), [参照2](https://github.com/Ryotaro25/leetcode_first60/pull/60/changes#diff-ee321728f766d10ee16b58e62bb4cd1e7423be9fab3820de1047fab4535dc44f)
  - [この人](https://github.com/olsen-blue/Arai60/pull/56/changes#:~:text=%2B-,%23%23%20%E8%A7%A3%E6%B3%951%3A%E7%B4%AF%E7%A9%8D%E5%92%8C%3AAC,-3)は一発で累積和に変換してる。
- `start = interval[0], end = interval[1]` とでもしたいかも。
- 色々考えようはあるんだな〜

埋めていくタイプの解法に対するコメント。確かに、マス目を埋めていくタイプの会議室予約であればこれで良いのだろうけど、もっと細かく見たい場合だと破綻するな。
> これでもいいですが、たとえば、時間が double になったときに使えないなど、色々と制約はありそうですね。
そういったことも考えていただけるとありがたいです。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/60/changes#r2003975631)

ソートだと入力破壊しちゃうか。ソートが一番しっくりきたので、`step2.cpp` ではその点を修正。

heap も使えるか。自然にできそう。`priority_queue` を使うが、min-heap にする必要がある。`heap.cpp` に書いた。

- [参照](https://github.com/hayashi-ay/leetcode/pull/59/changes#:~:text=heap%E3%82%92%E4%BD%BF%E3%81%A3%E3%81%9F%E8%A7%A3%E6%B3%95%E3%80%82%E3%81%93%E3%81%AE%E5%95%8F%E9%A1%8C%E3%81%A7%E3%81%AF%E3%82%BD%E3%83%BC%E3%83%88%E3%81%AB%E5%AF%BE%E3%81%97%E3%81%A6%E5%84%AA%E4%BD%8D%E6%80%A7%E3%81%AF%E3%81%AA%E3%81%84%E3%80%81%E8%A8%88%E7%AE%97%E9%87%8F%E7%9A%84%E3%81%AB%E3%81%AF%E5%90%8C%E3%81%98%E3%81%A0%E3%81%8C%E3%80%81%E3%82%BD%E3%83%BC%E3%83%88%E3%81%AE%E6%96%B9%E3%81%AFC%E3%81%A7%E6%9B%B8%E3%81%8B%E3%82%8C%E3%81%9F%E3%82%B3%E3%83%BC%E3%83%89%E3%81%8C%E5%8B%95%E3%81%8F%E5%88%86%E6%97%A9%E3%81%84%E6%B0%97%E3%81%8C%E3%81%99%E3%82%8B%E3%80%82)
- 参照コードのようなシンプルさはなくて、ちょっと残念。

## Step 3

`step3.cpp` に書いた。
