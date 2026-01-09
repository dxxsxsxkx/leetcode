# Step 1

## 1回目

### コード

列の要素を縦軸と横軸にとるグリッドの中を探索するイメージ。
グリッドの input は二つの値の和になるので、このうちの対角部分を除いた場所が答えの候補。数列の要素を事前に昇順ないし降順にソートしておいて、小さい方から順に調べていく。

下のコードを書いた。`pop()` の位置がおかしくて TLE になった。

```cpp
#include <vector>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<int> sort(nums.begin(), nums.end()); 
        std::vector<int> &nums1 = nums; 
        std::vector<int> &nums2 = nums; 

        auto compareSums = [&nums1, &nums2](IndexPair& a, IndexPair&b) {
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second]; 
        }; 
        priority_queue<IndexPair, vector<IndexPair>, decltype(compareSums)> pairs(compareSums); 

        for (int idx1 = 0; idx1 < nums1.size(); idx1++) {
            pairs.emplace(idx1, 0); 
        }

        int sum_two_elements; 
        std::vector<int> two_elements; 
        while(!pairs.empty()) {
            auto [idx1, idx2] = pairs.top(); 
            if (idx1 == idx2) {
                continue; 
            }
            pairs.pop();  // ここが変
            sum_two_elements = nums1[idx1] + nums2[idx2]; 
            if (sum_two_elements == target) {
                two_elements.push_back(idx1);
                two_elements.push_back(idx2); 
                break; 
            }
            if (idx2 + 1 < nums2.size()) {
                pairs.emplace(idx1, idx2 + 1); 
            }
        }

        return two_elements; 
    }
private: 
    using IndexPair = std::pair<int, int>; 
};
```

### メモ

なんか効率が悪いっぽい。

- 最悪の場合の時間計算量が $O(n^2 \log n^2)$。全探索する羽目になった場合にそうなる。

- 空間計算量は $O(n^2)$。

## 2回目

### コード

上のコードを書き直して通った。
VSCode上でコンパイルが通ることを確認。

```cpp
#include <vector>
#include <queue>
#include <algorithm>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<int> nums1 = nums; 
        std::vector<int> nums2 = nums; 
        sort(nums.begin(), nums.end()); 
        
        auto compareSums = [&nums1, &nums2](const IndexPair& a, const IndexPair&b) {
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second]; 
        }; 
        std::priority_queue<IndexPair, std::vector<IndexPair>, decltype(compareSums)> pairs(compareSums); 

        for (int idx1 = 0; idx1 < nums1.size(); idx1++) {
            pairs.emplace(idx1, 0); 
        }

        int sum_two_elements; 
        std::vector<int> two_elements; 
        while (!pairs.empty()) {
            auto [idx1, idx2] = pairs.top(); 
            pairs.pop(); 
            if (idx1 == idx2) {
                continue; 
            }
            sum_two_elements = nums1[idx1] + nums2[idx2]; 
            if (sum_two_elements == target) {
                two_elements.push_back(idx1); 
                two_elements.push_back(idx2); 
                break; 
            }
            if (idx2 + 1 < nums2.size()) {
                pairs.emplace(idx1, idx2 + 1); 
            }
        }

        return two_elements; 
    }
private: 
    using IndexPair = std::pair<int, int>; 
};
```

### メモ

他にも色々とややこしくしてしまっている。

- 元の配列のインデックスを返さなければいけないのにも関わらずソートしてしまうので、nums の配列は崩れる。そのせいで nums1 と nums2 という余計なオブジェクトを作る必要が生じている。

# Step 2

## 勉強

[参考](https://github.com/Ryotaro25/leetcode_first60/pull/12/commits/9c80068466e83724dc9004bca374e26f2b130b95#diff-c6f3dae85d58c942e719b6920512da2c4cb83c714737a676fd3258a12db0dede)。

- アプローチを考え直す：<数値, index> という hash table を作っておく。配列から一つ要素を取ってきて target との差分を計算し、hash table の中に合致する数値があれば hash table の index を返す。なければ今見た要素を hash table に入れて次の要素に進む。

  - このやり方であれば同じindexを取ることはなくなる（すでに見たindexしかhash tableに入らないので）。

- 解なしのケースも考慮する。

どの型を使うか？例えば、`contains` を使ってコンテナ内を探索する際の所要時間に差がある。

- [unordered_map](https://en.cppreference.com/w/cpp/container/unordered_map/contains) の complexity: "Constant on average, worst case linear in the size of the container"。こっちは hash table。C++20から実装されている。

- [map](https://en.cppreference.com/w/cpp/container/map/contains) の complexity: "Logarithmic in the size of the container"。こちらは平衡二分探索木。C++20から実装されている。

[参考](https://discord.com/channels/1084280443945353267/1183683738635346001/1187326805015810089)

- 別のアプローチ：
  > 私は紙と鉛筆でやるんだったら、カードをソートして、頭と尻から辿っていくと思いますね。はじめに、一番初めと一番最後に着目します。着目しているものを足します。目標よりも小さかったら、前の方の着目しているのを一つ後ろにずらします。目標よりも大きかったら、後ろの方の着目しているのを一つ前にずらします。繰り返したら見つかるはずです。

  - ソートした配列の前後から探索していく。目標にぶつかったら、対応する値のインデックスを元の配列から返す。元のインデックスを返すところがトリッキーかも。
  ```cpp
  #include <vector>
  #include <algorithm>

  class Solution {
  public:
      vector<int> twoSum(vector<int>& nums, int target) {
          std::vector<int> sorted_nums = nums; 
          std::sort(sorted_nums.begin(), sorted_nums.end()); 
          int left = 0; 
          int right = sorted_nums.size() - 1; 

          while (left < right) {
              int sum_two_elements = sorted_nums[left] + sorted_nums[right]; 
              if (sum_two_elements == target) {
                  int value_first = sorted_nums[left]; 
                  int value_second = sorted_nums[right]; 
                  int idx1 = -1; 
                  int idx2 = -1; 

                  for (int i = 0; i < nums.size(); i++) {
                      if (idx1 == -1 && nums[i] == value_first) {
                          idx1 = i; 
                      } else if (idx2 == -1 && nums[i] == value_second) {
                          idx2 = i; 
                      }
                  }

                  if (idx1 != -1 && idx2 != -1 && idx1 != idx2) {
                      return {idx1, idx2}; 
                  }
              } else if (sum_two_elements < target) {
                  left++; 
              } else {
                  right--; 
              }
          }


          std::vector<int> two_indices; 

          return {}; 
      }
  };
  ```

    - 元の配列の探索のところをもっとシンプルにできないだろうか？pair を使うとこういう風にできる。
    ```cpp
    #include <vector>
    #include <algorithm>

    class Solution {
    public:
        std::vector<int> twoSum(std::vector<int>& nums, int target) {
            std::vector<std::pair<int,int>> num_and_index;
            for (int i = 0; i < nums.size(); i++) {
                num_and_index.emplace_back(nums[i], i);
            }

            std::sort(num_and_index.begin(), num_and_index.end());

            int left = 0;
            int right = num_and_index.size() - 1;

            while (left < right) {
                int sum = num_and_index[left].first + num_and_index[right].first;
                if (sum == target) {
                    return {num_and_index[left].second, num_and_index[right].second};
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }

            return {}; 
        }
    };
    ```

2重ループで書く。内側のループのインデックスをうまく設定すると効率が良い（余計な要素を見なくて良いのと、`i == j` のケースを考えなくていい）。

```cpp
#include <vector>

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::vector<int> two_indices; 

        for (int i = 0; i < nums.size(); i++) {
          for (int j = i + 1; j < nums.size(); j++) {
            int sum_two_elements = nums[i] + nums[j]; 
            if (sum_two_elements == target) {
              return {i, j}; 
            }
          }
        }

        return {}; 
    }
};
```

- [参照](https://github.com/Ryotaro25/leetcode_first60/pull/12/commits/9c80068466e83724dc9004bca374e26f2b130b95#r1634189928)。

その他の点。

- 解が一意に定まることが保証されているので `two_indices` を作る必要はないか。

## コード

`unordered_map` を使う。`map`でも同じようにかける。

```cpp
#include <vector>
#include <unordered_map>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> nums_to_indices; 
        std::vector<int> two_indices; 

        for (int i = 0; i < nums.size(); i++) {
            int diff = target - nums[i]; 
            if (nums_to_indices.contains(diff)) {
                return {nums_to_indices[diff], i}; 
            }
            nums_to_indices.insert({nums[i], i}); 
        }

        return two_indices; 
    }
};
```

# Step 3

どの方法が一番良いかで迷う。
