#include <vector>
#include <queue>
#include <algorithm>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::vector<int> nums1 = nums; 
        std::vector<int> nums2 = nums; 
        sort(nums.begin(), nums.end()); 
        
        auto compareSums = [&nums1, &nums2](const IndexPair& a, const IndexPair&b) {
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second]; 
        }; 
        std::priority_queue<IndexPair, std::vector<IndexPair>, decltype(compareSums)> pairs(compareSums); 

        for (int idx1 = 0; idx1 < nums1.size(); idx1++) {
            pairs.emplace(idx1, 0); 
        }

        int sum_two_elements; 
        std::vector<int> two_elements; 
        while (!pairs.empty()) {
            auto [idx1, idx2] = pairs.top(); 
            pairs.pop(); 
            if (idx1 == idx2) {
                continue; 
            }
            sum_two_elements = nums1[idx1] + nums2[idx2]; 
            if (sum_two_elements == target) {
                two_elements.push_back(idx1); 
                two_elements.push_back(idx2); 
                break; 
            }
            if (idx2 + 1 < nums2.size()) {
                pairs.emplace(idx1, idx2 + 1); 
            }
        }

        return two_elements; 
    }
private: 
    using IndexPair = std::pair<int, int>; 
};
