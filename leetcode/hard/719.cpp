#include <vector>
#include <algorithm>

class Solution {
public:
  int smallestDistancePair(std::vector<int> &nums, int k) {
    std::sort(nums.begin(), nums.end());
    int n = nums.size();
    int l = 0, h = nums[n - 1] - nums[0];
    auto count = [&](int v) {
      int p1 =
          std::distance(nums.begin(), std::upper_bound(nums.begin(), nums.end(),
                                                       nums[0] + v));
      int ret = p1 - 1;
      for (int i = 1; i < n; ++i) {
        int nv = nums[i] + v;
        while (p1 < n && nums[p1] <= nv) {
          ++p1;
        }
        ret += p1 - i - 1;
      }
      return ret;
    };
    if (count(0) >= k) {
      return 0;
    }
    while (l + 1 != h) {
      int m = l + (h - l) / 2;
      if (count(m) >= k) {
        h = m;
      } else {
        l = m;
      }
    }
    return h;
  }
};
