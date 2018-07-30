#include <algorithm>
#include <iterator>
#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> permuteUnique(std::vector<int> &nums) {
    int n = nums.size();
    auto next = [&]() -> bool {
      int i;
      for (i = n - 2; i >= 0; --i) {
        if (nums[i] < nums[i + 1]) {
          break;
        }
      }
      if (i < 0) {
        return false;
      }
      int pos = std::distance(nums.begin() + i + 1,
                              std::lower_bound(nums.begin() + i + 1, nums.end(),
                                               nums[i], std::greater<int>())) -
                1;
      std::swap(nums[i], nums[i + 1 + pos]);
      std::reverse(nums.begin() + i + 1, nums.end());
      return true;
    };
    std::vector<std::vector<int>> ret;
    std::sort(nums.begin(), nums.end());
    ret.push_back(nums);
    while (next()) {
      ret.push_back(nums);
    }
    return ret;
  }
};
