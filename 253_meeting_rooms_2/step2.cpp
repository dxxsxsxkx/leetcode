#include <algorithm>
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
    int minMeetingRooms(std::vector<Interval>& intervals) {
        std::vector<std::pair<int, int>> events;
        for (const Interval& interval : intervals) {
            // start: need one more room
            // end: need one less room
            events.emplace_back(interval.start, 1);
            events.emplace_back(interval.end, -1);
        }

        std::sort(events.begin(), events.end(), 
            [](const auto& a, const auto& b) {
                if (a.first == b.first) {
                    return a.second < b.second;
                }
                return a.first < b.first;
            }
        );

        int min_required_rooms = 0;
        int num_rooms = 0;
        for (const auto& event : events) {
            num_rooms += event.second; 
            min_required_rooms = std::max(min_required_rooms, num_rooms);
        }
        return min_required_rooms;
    }
};
