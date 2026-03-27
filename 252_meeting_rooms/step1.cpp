#include <utility>
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
        for (int i = 0; i < intervals.size(); ++i) {
            for (int j = i + 1; j < intervals.size(); ++j) {
                std::pair<Interval, Interval> two_intervals = {intervals[i], intervals[j]};
                if (isConflict(two_intervals)) {
                    return false;
                }
            }
        }
        return true;
    }
private:
    bool isConflict(const std::pair<Interval, Interval>& intervals) {
        if (intervals.first.end > intervals.second.start && 
            intervals.second.end > intervals.first.start) {
            return true;
        }
        return false;
    }
};

