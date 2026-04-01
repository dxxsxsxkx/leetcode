#include <algorithm>
#include <queue>
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
    int minMeetingRooms(std::vector<Interval>& intervals) {
        if (intervals.empty()) {
            return 0;
        }
        
        std::vector<Interval>& sorted = intervals;
        std::sort(sorted.begin(), sorted.end(), 
            [](const Interval& a, const Interval& b) {
                return a.start < b.start;
            }
        );

        // contains ongoing meetings
        std::priority_queue<int, std::vector<int>, std::greater<int>> ongoing_meetings;
        
        for (const auto& interval : intervals) {
            // if the earliest-ending meeting ends before the next meeting begins, 
            // we can use the room occupied by the ending meeting
            if (!ongoing_meetings.empty() && ongoing_meetings.top() <= interval.start) {
                ongoing_meetings.pop();
            }
            ongoing_meetings.push(interval.end);
        }
        return ongoing_meetings.size();
    }
};
