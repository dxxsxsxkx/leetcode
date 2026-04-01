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
        std::vector<Interval>& sorted = intervals;
        std::sort(sorted.begin(), sorted.end(), 
            [](const Interval& a, const Interval& b) {
                return a.start < b.start;
            }
        );

        std::priority_queue<int, std::vector<int>, std::greater<int>> ongoing_meetings; 

        for (auto& interval : intervals) {
            // if the earliest-ending meeting ends before the next meeting, 
            // we can use the room that was previously occupied
            if (!ongoing_meetings.empty() && ongoing_meetings.top() <= interval.start) {
                ongoing_meetings.pop();
            }
            ongoing_meetings.push(interval.end);
        }
        return ongoing_meetings.size();
    }
};
