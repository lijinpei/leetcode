#include <algorithm>
#include <functional>
#include <vector>

class Solution {
public:
  bool search(std::vector<int> &nums, int target) {
    int n = nums.size();
    if (!n) {
      return false;
    }
    int mv = nums[0];
    if (target == mv) {
      return true;
    }
    int i = 1;
    for (; i < n; ++i) {
      if (nums[i] != mv) {
        break;
      }
    }
    int m = std::distance(nums.begin(),
                          std::lower_bound(nums.begin() + i, nums.end(), mv,
                                           std::greater<int>()));
    int p;
    if (m == n || target > mv) {
      p = std::distance(
          nums.begin(),
          std::lower_bound(nums.begin(), nums.begin() + m, target));
    } else {
      p = std::distance(nums.begin(),
                        std::lower_bound(nums.begin() + m, nums.end(), target));
    }
    return p < n && nums[p] == target;
  }
};
