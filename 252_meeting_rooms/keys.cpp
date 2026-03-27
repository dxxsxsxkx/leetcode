#include <map>
#include <vector>
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
    bool canAttendMeetings(vector<Interval>& intervals) {
        std::map<int, int> num_keys_needed;
        for (auto interval : intervals) {
            ++num_keys_needed[interval.start];  // take the key
            --num_keys_needed[interval.end];  // return the key
        }

        int num_keys = 0;
        for (auto [time, num_key] : num_keys_needed) {
            num_keys += num_key;
            if (num_keys > 1) {
                return false;
            }
        }
        return true;
    }
};
