# Step 1

## 1回目

Subarray の和を key, 要素数を value にする `map` を作る。
Array の要素を左から見ていき、その要素と次の要素の和をキーとして要素数を1増やす。
別途、最初の要素と最後の要素を見るときだけ、その要素の値をキーとする要素数を1増やす。

### コード

```cpp
#include <map>
#include <vector>

class Solution {
public:
    int subarraySum(std::vector<int>& nums, int k) {
        std::map<int, int> sum_to_count; 
        for (int i = 0; i < nums.size(); i++) {
            sum_to_count[nums[i] + nums[i + 1]]++; 
            if (i == 0 || i == nums.size() - 1) {
                sum_to_count[nums[i]]++; 
            }
        }

        return sum_to_count[k]; 
    }
};
``` 

### メモ

たまたま通っているだけで問題点がたくさんある。

- `nums[i + 1]` は範囲外アクセスになりうる。

- 要素2以下のケースしか考えていない; 3以上でもありうる。

# Step 2

## 勉強

累積和を使う。

```cpp
#include <map>
#include <vector>

class Solution {
public:
    int subarraySum(std::vector<int>& nums, int k) {
        std::map<int, int> prefix_count; 
        prefix_count[0] = 1; 
        
        int sum = 0; 
        int answer = 0; 

        for (int num : nums) {
            sum += num; 
            if (prefix_count.contains(sum - k)) {
                answer += prefix_count[sum - k]; 
            }
            prefix_count[sum]++; 
        }
        return answer; 
    }
};
```

- `prefix[i] = nums[0] + ... + nums[i]` の時、区間 `[l + 1, r]` の和は `prefix[r] - prefix[l]` になる。
これが `k` に等しいのであれば、`prefix[l] = prefix[r] - k` となる。
このことを利用して、`answer += prefix_count[sum - k];` ではその要素までの累積和が k になるような要素の数を調べている。
> 問いは`sums[j] - sums[i] = k (i < j)` となる `i,j` のペアの数を求めることと読み換えられる。

  - この制約を適当に変形することで色々書き方が変わってくる。例えば、そのままの形であれば2重ループにして差が k になることを調べることになる。
  ```cpp
  // 時間がかかる
  #include <map>
  #include <vector>

  class Solution {
  public:
      int subarraySum(std::vector<int>& nums, int k) {
          int answer = 0; 

          for (int i = 0; i < nums.size(); i++) {
              for (int j = i; j < nums.size(); j++) {
                  int sum = 0; 
                  for (int k = i; k <= j; k++) {
                      sum += nums[k];
                  }
                  if (sum == k) {
                      answer++;
                  }
              }
          }
          return answer; 
      }
  };
  ```

  - あるいは、右に腕を伸ばしていく。
  ```cpp
  #include <map>
  #include <vector>

  class Solution {
  public:
      int subarraySum(std::vector<int>& nums, int k) {
          int answer = 0; 

          for (int i = 0; i < nums.size(); i++) {
              int sum = 0; 
              for (int j = i; j < nums.size(); j++) {
                  sum += nums[j]; 
                  if (sum == k) {
                      answer++; 
                  }
              }
          }
          return answer; 
      }
  };
  ```

  - こういうやり方だと、同じ部分和の計算を何度も何度も繰り返していることになる。なので、都度都度部分和を保存しておいて後から見れば良いじゃんということになる。

- [コメント](https://discord.com/channels/1084280443945353267/1233603535862628432/1252232545056063548): 
> ちょっと問題を変えて、和が K となる区間を列挙する問題にしてみたらどうでしょうか。もうちょっと言い換えると、「鉄道があって、各駅間ごとの標高差が与えられます。
標高差が ちょうど K であるようなすべての駅の組み合わせを列挙してください。」ということです。
最後に len を取れば、元の問題の答えになるはずなので、ジャッジも使えるでしょう。これを累積和を使って出してください。

  - 山の絵を描いてみた。駅に着いたらまずその時点での累積標高を記録する。次に、これまでの累積標高の記録を取り出して、今の駅との差が k になるような駅の数を調べる。
  あったら足す。

- 累積和の計算には [`std::partial_sum(first, last, d_first)`](https://en.cppreference.com/w/cpp/algorithm/exclusive_scan) が使える（C++20から）。
  ```cpp
  #include <map>
  #include <numeric>
  #include <vector>

  class Solution {
  public:
      int subarraySum(std::vector<int>& nums, int k) {
          std::vector<int> prefix(nums.size());
          std::partial_sum(nums.begin(), nums.end(), prefix.begin());

          std::map<int, int> prefix_count;
          prefix_count[0] = 1;

          int answer = 0;
          for (int p : prefix) {
              if (prefix_count.contains(p - k)) {
                  answer += prefix_count[p - k];
              }
              prefix_count[p]++;
          }
          return answer;
      }
  };
  ```

# Step 3

書けた。`prefix` を `cumsum` にした。あと `answer` は `count_k` にした。
