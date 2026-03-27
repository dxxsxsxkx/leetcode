#include <algorithm>
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
    bool canAttendMeetings(std::vector<Interval>& intervals) {
        if (intervals.size() <= 1) {
            return true;
        }
        
        std::sort(intervals.begin(), intervals.end(), 
            [](const Interval& a, const Interval& b) {
                return a.start < b.start;
            }
        );

        for (int i = 0; i < intervals.size() - 1; ++i) {
            if (intervals[i].end > intervals[i + 1].start) {
                return false;
            }
        }
        return true;
    }
};
