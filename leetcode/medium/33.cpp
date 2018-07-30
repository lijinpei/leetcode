#include <algorithm>
#include <functional>
#include <vector>

class Solution {
public:
  int search(std::vector<int> &nums, int target) {
    int n = nums.size();
    if (!n) {
      return -1;
    }
    if (n == 1) {
      return target == nums[0] ? 0 : -1;
    }
    int m = std::distance(nums.begin(),
                          std::lower_bound(nums.begin() + 1, nums.end(),
                                           nums[0], std::greater<int>()));
    int p;
    if (target > nums[n - 1] || m == n) {
      p = std::distance(
          nums.begin(),
          std::lower_bound(nums.begin(), nums.begin() + m, target));
    } else {
      p = std::distance(nums.begin(),
                        std::lower_bound(nums.begin() + m, nums.end(), target));
    }
    return (p < n && nums[p] == target) ? p : -1;
  }
};
