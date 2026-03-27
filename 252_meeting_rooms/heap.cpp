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
    bool canAttendMeetings(std::vector<Interval>& intervals) {
        auto comparison = [](const Interval& a, const Interval& b) {
            return a.start > b.start;
        };

        std::priority_queue<
            Interval, 
            std::vector<Interval>, 
            decltype(comparison)
        > pq(comparison);

        for (const auto& interval : intervals) {
            pq.push(interval);
        }

        int previous_end = -1;

        while (!pq.empty()) {
            Interval current_schedule = pq.top();
            pq.pop();

            if (current_schedule.start < previous_end) {
                return false;
            }
            previous_end = current_schedule.end;
        }
        return true;
    }
};
