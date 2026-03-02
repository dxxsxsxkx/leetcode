#include <vector>
class Solution {
public:
    int searchInsert(std::vector<int>& nums, int target) {
        if (nums.empty()) {
            return 0;
        }

        // 閉区間にする
        // つまり、答えが [begin, end] の中にある状態を保つ
        int begin = 0;
        int end = nums.size() - 1;

        int answer = nums.size();

        // 一意に定まったら終了、つまり begin > end となったら終了
        while (begin <= end) {
            int mid = begin + (end - begin) / 2;

            // 閉区間の場合、mid が begin と一致すると区間が縮まらない
            if (target <= nums[mid]) {
                answer = mid;  // true の頭を取る
                end = mid - 1;  // さらに左側を探索
            } else {
                begin = mid + 1;  // false 側を捨てる
            }
        }

        return answer;
    }
};
