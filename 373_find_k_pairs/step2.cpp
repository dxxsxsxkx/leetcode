#include <queue>
#include <vector>

class Solution{
public: 
  std::vector<std::vector<int>> kSmallestPairs(
    std::vector<int>& nums1,
    std::vector<int>& nums2,
    int k
  ){
    if (nums1.empty() || nums2.empty() || k == 0) {
      return {}; 
    }

    auto compareSums = [&nums1, &nums2](IndexPair& a, IndexPair&b) {
      return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second]; 
    };
    std::priority_queue<IndexPair, std::vector<IndexPair>, decltype(compareSums)> all_pairs(compareSums); 
    std::vector<std::vector<int>> k_smallest_pairs; 
    
    for (int id1 = 0; id1 < nums1.size(); id1++) {
      all_pairs.emplace(id1, 0); 
    }

    for (int i = 0; i < k; i++) {
      auto [id1, id2] = all_pairs.top(); 
      all_pairs.pop(); 
      k_smallest_pairs.push_back({nums1[id1], nums2[id2]}); 
      if (id2 + 1 < nums2.size()) {
        all_pairs.emplace(id1, id2 + 1); 
      }
    }

    return k_smallest_pairs; 
  }

private:
  using IndexPair = std::pair<int, int>; 
}; 
