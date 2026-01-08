#include <queue>

class Solution {
public:
    std::vector<std::vector<int>> kSmallestPairs(std::vector<int>& nums1, std::vector<int>& nums2, int k) {
        auto compareSums = [&nums1, &nums2](IndexPair& a, IndexPair&b) {
            return nums1[a.first] + nums2[a.second] > nums2[b.first] + nums2[b.second]; 
        };

        std::priority_queue<IndexPair, std::vector<IndexPair>, decltype(compareSums)> all_pairs(compareSums); 
        std::vector<std::vector<int>> k_smallest_sums; 

        for (int i = 0; i < nums1.size(); i++) {
            all_pairs.emplace(i, 0); 
        }

        while (k-- > 0) {
            auto [index1, index2] = all_pairs.top(); 
            all_pairs.pop(); 
            k_smallest_sums.push_back({nums1[index1], nums2[index2]}); 
            if (index2 + 1 < nums2.size()) {
                all_pairs.emplace(index1, index2 + 1);
            }
        }
        return k_smallest_sums;
    }
private: 
    typedef std::pair<int, int> IndexPair;
};
