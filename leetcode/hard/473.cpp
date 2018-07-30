#include <vector>
#include <functional>

class Solution {
  static bool search(std::vector<int>& nums, int n, int (&arr)[4], int t) {
    if (n == nums.size()) {
      return true;
    }
    int v = nums[n];
    for (int i = 0; i < 4; ++i) {
      if (arr[i] + v > t) {
        continue;
      }
      bool same = false;
      for (int j = 0; j < i; ++j) {
        if (arr[i] == arr[j]) {
          same = true;
          break;
        }
      }
      if (same) {
        continue;
      }
      arr[i] += v;
      if (search(nums, n + 1, arr, t)) {
        return true;
      }
      arr[i] -= v;
    }
    return false;
  }
public:
  bool makesquare(std::vector<int>& nums) {
    int s = 0;
    for (auto v : nums) {
      s += v;
    }
    if (s % 4) {
      return false;
    }
    if (nums.size() < 4) {
      return false;
    }
    std::sort(nums.begin(), nums.end(), std::greater<int>());
    int arr[4] = {};
    return search(nums, 0, arr, s / 4);
  }
};
