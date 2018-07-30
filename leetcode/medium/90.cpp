#include <vector>
#include <algorithm>

class Solution {
  std::vector<std::vector<int>> ret;
  void search(std::vector<int> & nums, int p, std::vector<int> sol) {
    int s = nums.size();
    if (p == s) {
      if (!sol.empty()) {
        ret.push_back(sol);
      }
      return;
    }
    int v = nums[p];
    int n = 1;
    for (++p ; p < s; ++p) {
      if (nums[p] != v) {
        break;
      }
      ++n;
    }
    std::vector<int> sol1;
    sol1.reserve(n + sol.size());
    sol1 = sol;
    for (int j = 0; j <= n; ++j) {
      search(nums, p, sol1);
      sol1.push_back(v);
    }
  }
public:
  std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums) {
    ret.push_back({});
    std::sort(nums.begin(), nums.end());
    search(nums, 0, {});
    return ret;
  }
};
