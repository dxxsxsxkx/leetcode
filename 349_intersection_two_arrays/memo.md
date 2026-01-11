# Step 1

## 1回目

### コード

nums1とnums2のそれぞれについて、整数の登場回数を記録する unordered_map を作成する。
片方のキーを取ってきて、もう片方のmapに入っているかをcontainsで確認し、入っていたらintersectionに入れる。

```cpp
#include <unordered_map>
#include <vector>

class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_map<std::vector<int>, std::vector<int>> num_to_count_1; 
        std::unordered_map<std::vector<int>, std::vector<int>> num_to_count_2; 
        for (int num1 : nums1) {
            num_to_count_1[num1]++; 
        }
        for (int num2 : nums2) {
            num_to_count_2[num2]++; 
        }

        std::vector<int> intersection; 
        for (auto& [key1, value1] : num_to_count_1) {
            if (num_to_count_2.contains(value1)) {
                intersection.push_back(value1); 
            }
        }

        return intersection; 
    }
};
```

書きながら、片方が超長かった場合には短い方を使ってループしないと面倒臭いか？とか考えたが、そうでもないのか？結局 contains で探すときに全部見る羽目になるのでは？とか思った。

- で、後でstep 2をやっているときに [unordered_set.contains()](https://en.cppreference.com/w/cpp/container/unordered_set/contains.html)を調べていて、ハッシュと計算量の話が結びついた。ハッシュで管理されたパケットに複数の要素が入り込むことが問題で、極端なのが全ての要素が一つのパケットに入ってしまう場合ということと理解した。「全部見る」というのがおかしくて、unordered_set.contains()であれば極端な場合以外はもっと短く済ませられるっぽい。

- この点については、例えば後のコードのところで `if (set1.size() > set2.size()) {swap(set1, set2)}` とかしてあげると良いのかも。

以下が問題点。

- ハッシュ関数が必要だが `std::vector<int>` にはデフォルトがない。

  - そもそも unordered_map は int / int で作る必要があるので irrelevant だが...。

- キーと値を勘違いしている。contains にキーではなく値を渡していたり、値を push_back したりしている。

## 2回目

上の問題を修正して書けた。

### コード

```cpp
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_map<int, int> num_to_count_1; 
        std::unordered_map<int, int> num_to_count_2; 
        for (int num1 : nums1) {
            num_to_count_1[num1]++; 
        }
        for (int num2 : nums2) {
            num_to_count_2[num2]++; 
        }

        std::vector<int> nums_intersection; 
        for (auto& [key1, value1] : num_to_count_1) {
            if (num_to_count_2.contains(key1)) {
                nums_intersection.push_back(std::move(key1)); 
            }
        }
        return nums_intersection; 
    }
};
```

- 考えてみると、出現回数は使っていない。`unordered_set`で十分。

- 計算量見積もり：列の長さを $n$ として時間 $O(n)$、空間 $O(n)$。

# Step 2

## 勉強

何を使うか問題。

- `unordered_set`で良い。contains / find が使える。

  ```cpp
  #include <unordered_set>
  #include <vector>

  class Solution {
  public:
      std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
          std::unordered_set<int> set1(nums1.begin(), nums1.end()); 
          std::unordered_set<int> set2(nums2.begin(), nums2.end()); 

          std::vector<int> nums_intersection; 
          for (int num : set1) {
              if (set2.contains(num)) {
                  nums_intersection.push_back(num); 
              }
          }
          return nums_intersection; 
      }
  };
  ```

  - ではなぜ `set` にしないのか？見直す：https://github.com/Ryotaro25/leetcode_first60/pull/14/commits/97f7114f04589703a3f3b8e7766ca483c0a6c8a0#r1638460693

- [条件によって変わる](https://discord.com/channels/1084280443945353267/1303257587742933024/1319664094235594824)。

  - すでにソートされている配列ならば、set や unordered_set を使って重複排除をする必要はない。
  
    - [コメント](https://github.com/katataku/leetcode/pull/12)：マージソートについては調べる。こういう感じでかける：

    ```cpp
    std::vector<int> intersection; 
    int i = 0;
    int j = 0; 

    while (i < nums1.size() && j < nums2.size()) {
      if (nums1[i] < nums2[j]) {
        i++; 
      } else if (nums1[i] > nums2[j]) {
        j++; 
      } else {
        if (intersection.empty() || intersection.back() != nums1[i]) {
          intersection.push_back(nums1[i]); 
        }
        i++;
        j++; 
      }
    }
    return intersection; 
    ```

    - 重複チェック：最後に入れた要素とダブってないかだけを見れば良い

ソートされていれば[set_intersection](https://en.cppreference.com/w/cpp/algorithm/set_intersection.html)も使える。setにすればこう書ける。`back_inserter`は出力範囲の先頭を指す。ここでは、nums_intersectionの後にpush_backしていくという意味になる。

```cpp
#include <algorithm>
#include <set>
#include <vector>

class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::unordered_set<int> set1(nums1.begin(), nums1.end()); 
        std::unordered_set<int> set2(nums2.begin(), nums2.end()); 

        std::vector<int> nums_intersection; 
        std::set_interaction(
            set1.begin(), set1.end(), 
            set2.begin(), set2.end(), 
            std::back_inserter(nums_intersection)
        ); 
        return nums_intersection; 
    }
};
```

# Step 3

問題なくかけた。swapを入れたりした。
