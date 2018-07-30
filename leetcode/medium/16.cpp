#include <vector>
#include <algorithm>
#include <limits>

class Solution {
public:
  int threeSumClosest(std::vector<int> &nums, int target) {
    std::sort(nums.begin(), nums.end());
    int ans = std::numeric_limits<int>::max(), ans_v;
    for (int i = 0, n = nums.size(); i + 2 < n; ++i) {
      int v1 = nums[i];
      for (int j = i + 1, k = n - 1; j + 1 < n; ++j) {
        int v2 = v1 + nums[j];
        int v3;
        while (k > j) {
          v3 = nums[k] + v2;
          if (v3 <= target) {
            break;
          }
          --k;
        }
        if (k != n - 1) {
          int ans1 = v2 + nums[k + 1] - target;
          if (ans1 < ans) {
            ans = ans1;
            ans_v = v2 + nums[k + 1];
            if (!ans) {
              return target;
            }
          }
        }
        if (k == j) {
          break;
        }
        int ans1 = target - v3;
        if (ans1 < ans) {
          ans = ans1;
          ans_v = v3;
          if (!ans) {
            return target;
          }
        }
      }
    }
    return ans_v;
  }
};
