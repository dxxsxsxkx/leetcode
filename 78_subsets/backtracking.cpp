#include <vector>
class Solution {
  public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
      std::vector<std::vector<int>> all_subsets;
      std::vector<int> subsets_already_made = {};
      GenerateSubset(nums, 0, subsets_already_made, all_subsets);
      return all_subsets;
    }
  private:
    void GenerateSubset(
      const std::vector<int>& nums, 
      int start, 
      std::vector<int>& subsets_already_made, 
      std::vector<std::vector<int>>& all_subsets
    ) {
      all_subsets.emplace_back(subsets_already_made);

      for (int i = start; i < nums.size(); ++i) {
        subsets_already_made.push_back(nums[i]);
        GenerateSubset(nums, i + 1, subsets_already_made, all_subsets);
        subsets_already_made.pop_back();
      }
    }
};
