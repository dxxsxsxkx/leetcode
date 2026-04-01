# 253. Meeting Rooms 2

## Step 1

与えられた会議のスケジュール全てを accomodate するために必要な最小の部屋数を返す。

- 制約：`0 <= intervals.length <= 500, 0 <= intervals[i].start < intervals[i].end <= 1,000,000`

最初にソートする。部屋の数を1からスタートさせて、conflict を検出するたびに1つずつ増やしていくか。

- ただし、ただ conflict があることを検出するだけではなくいくつの会議がぶつかっているかを確かめる必要がある。検出した conflict の数を現状の部屋の数と比較して大きい方を取れば良い。
- 検出の仕組み。スタート時間でソートしておけば、前方向に伸ばしていって conflict しなくなったところで止まれば良さそう。これだとある会議がいくつの会議とバッティングするかを調べることになる。
  - 起点を与えておく？
- こんな感じで書いてWAに。30分ほど経ったので答えを見る。

  ```cpp
    /**
   * Definition of Interval:
  * class Interval {
  * public:
  *     int start, end;
  *     Interval(int start, int end) {
  *         this->start = start;
  *         this->end = end;
  *     }
  * }
  */

  class Solution {
  public:
      int minMeetingRooms(std::vector<Interval>& intervals) {
          if (intervals.size() == 0) {
              return 0;
          }
          if (intervals.size() == 1) {
              return 1;
          }

          std::vector<Interval>& sorted = intervals;
          std::sort(sorted.begin(), sorted.end(), 
              [](const Interval& a, const Interval& b) {
                  return a.start < b.start;
              }
          );

          // At least 1 room is guaranteed to be necessary
          int num_rooms = 1;
          for (int i = 0; i < sorted.size() - 1; ++i) {
              int num_conflicts = countConflictingMeetings(sorted, i);
              num_rooms = std::max(num_rooms, num_conflicts);
          }

          return num_rooms;
      }
  private:
      // intervals are sorted
      int countConflictingMeetings(const std::vector<Interval>& intervals, const int start) {
          int num_conflicts = 0;
          for (int i = start; i < intervals.size() - 1; ++i) {
              if (intervals[i].end <= intervals[i + 1].start) {
                  break;
              }
              ++num_conflicts;
          }
          return num_conflicts;
      }
  };
  ```

色々間違っている。

- まず考え方が違う。それぞれの会議が後ろの会議と何個連続で衝突するかを見るのだと、ある会議が後ろの会議と細切れに（？）衝突するケースが扱えない。
  - 例：`[0, 40], [5, 10], (15, 20)`
  - 本来考えるべきは同時進行している会議の最大値。
- 必要な部屋数は衝突の数 + 1。

`step1.cpp` に書いた。

- min-heap を使って進行中の会議を管理する（heap には終了時刻を入れておく）。heap の先頭（min-heap なので一番最初に終わる会議）が次の会議のスタートよりも小さかったら、次の会議が始まる時に前の会議が終わっていてその部屋を使えるので pop する。

## Step 2

それぞれの会議の start と end に必要な部屋数の変化（+1 / -1）を結びつけ、これを累積する。

```cpp
/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        std::vector<std::pair<int, int>> events;
        for (const Interval& interval : intervals) {
            // start: need one more room
            // end: need one less room
            events.emplace_back(interval.start, 1);
            events.emplace_back(interval.end, -1);
        }

        std::sort(events.begin(), events.end(), 
            [](const auto& a, const auto& b) {
                if (a.first == b.first) {
                    return a.second < b.second;
                }
                return a.first < b.first;
            }
        );

        int min_required_rooms = 0;
        int num_rooms = 0;
        for (const auto& event : events) {
            num_rooms += event.second; 
            min_required_rooms = std::max(min_required_rooms, num_rooms);
        }
        return min_required_rooms;
    }
};
```

- [参照](https://github.com/potrue/leetcode/pull/56/changes)
  - 代替問題の方では `multimap` だとうまくいかず。start と end が同時刻の2つの会議があった場合、`multimap` では順序が不適切になる。本来であれば終わる方の会議から処理しなければいけないが、`multimap` では順序が挿入順に依存する。
    - [こういうやり方](https://github.com/Ryotaro25/leetcode_first60/pull/61#discussion_r2005183830)もあるが、確かにパズルになっている。
  - とりあえず、`pair` を使った上でソートしている。これは、最初このコードを見た時にはわからなかった。
    - 他の言語だと色々難しさがあるのか。[参照: javaのケース](https://github.com/goto-untrapped/Arai60/pull/61/changes#r1782986238)
- LLMに聞いたらスイープラインというらしいが、つながりにピンときていない。
  - [Wiki](https://en.wikipedia.org/wiki/Sweep_line_algorithm)
- 使わない変数の型を書くとノイズになるかも、という見方（`auto& [_, xxx]` みたいにする）
  - [参照](https://github.com/potrue/leetcode/pull/56/changes#r2296720446)
- 前の問題で鍵と書いていたところ「部屋とも考えられるよね」というコメントがついていたが、やってみると確かに。問題のコンテクストに左右される。
  - ちなみに[このコード](https://github.com/Ryotaro25/leetcode_first60/pull/61/changes#diff-b75c5529b80022de970a00ed7900115f18584ee0814dce90140f3cb2e9e42b8a)だと鍵のイメージになっている

`time` ってまずいのか！`time.h` 知らなかった。でも調べてみたら冷静にすでに使われていて当然という感じはした。
> time は C++ では time.h の time を思い浮かべますね。後使っていないので、警告が出ることがあるが、structured bindings では難しいなどの話があります。

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/61/changes#r2005191194)
- [`time`について](https://learn.microsoft.com/ja-jp/cpp/c-runtime-library/reference/time-time32-time64?view=msvc-170)

`emplace_back` 意味ある？内部的には `pair<int, int>` をその場で構築して追加している。ここではこの型が軽いのでわざわざ使うメリットはそれほどないかも。

## Step 3

min-heap を使うバージョンとイベントごとに処理していく方法を両方練習。

`step3.cpp` には queue の方を書いた。他のPRで会議がない場合の処理を分けていないと気になる、というのがあり、確かにそうだと思ったので冒頭に追加した。
