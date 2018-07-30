#include <vector>
#include <algorithm>

class Solution {
  // first not less than
  static size_t my_lower_bound(const std::vector<int> &nums, int target) {
    int n = nums.size();
    if (nums[n - 1] < target) {
      return n;
    }
    int l = 0, r = n;
    while (l + 1 != r) {
      int m = l + (r - l - 1) / 2;
      int v = nums[m];
      if (v >= target) {
        r = m + 1;
      } else {
        l = m + 1;
      }
    }
    return l;
  }
  // first greater than
  static size_t my_upper_bound(const std::vector<int> &nums, int target) {
    int n = nums.size();
    if (nums[n - 1] <= target) {
      return n;
    }
    int l = 0, r = n;
    while (l + 1 != r) {
      int m = l + (r - l - 1) / 2;
      int v = nums[m];
      if (v <= target) {
        l = m + 1;
      } else if (v > target) {
        r = m + 1;
      }
    }
    return l;
  }

public:
  std::vector<int> searchRange(std::vector<int> &nums, int target) {
    if (nums.size() == 0) {
      return {-1, -1};
    }
    // int v1 = my_lower_bound(nums, target);
    int v1 = std::distance(nums.begin(),
                           std::lower_bound(nums.begin(), nums.end(), target));
    if (v1 == int(nums.size()) || nums[v1] != target) {
      return {-1, -1};
    }
    // int v2 = my_upper_bound(nums, target);
    int v2 = std::distance(nums.begin(),
                           std::upper_bound(nums.begin(), nums.end(), target));
    if (v2 == 0 || nums[v2 - 1] != target) {
      return {-1, -1};
    }
    return {v1, v2 - 1};
  }
};
