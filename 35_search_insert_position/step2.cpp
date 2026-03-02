#include <vector>
class Solution {
public:
    // 1. [false, false, false, ..., true, true, true] となる列において、
    //  一番最初の true となるインデックスを返す問題だと考える
    // 2. 答えが含まれる範囲を狭めていって、最後に残ったインデックスを返す
    //  - 半閉区間 [begin, end) を使う。
    int searchInsert(std::vector<int>& nums, int target) {
        // 8. エッジケース：空リスト
        if (nums.empty()) {
            return 0;
        }

        // 3. 最初は 0 から nums.size() までを考える
        int begin = 0; 
        int end = nums.size();

        // 4. 最後に残ったインデックスを判定する際には、begin < end を使う
        //  - `begin > end` になった場合には終了
        while (begin < end) {
            // 5. 半分に切っていって、中間点がどちらの区間に入るかで考慮する区間を絞る
            //  - 常に [begin, end] の区間が答えを含むようにする
            //  - integer overflow に注意
            int mid = begin + (end - begin) / 2;

            // 6. `target` が mid に対してどの位置にあるかで絞り込み
            //  - 右側を閉じる
            if (target <= nums[mid]) {
                end = mid;
            } else {
                begin = mid + 1;
            }
        }

        // 7. 最後は begin == end となる
        return begin;
    }
};
