#include <vector>

class Solution {
  static void subset(std::vector<std::vector<int>> & ret, const std::vector<int> & nums, int p) {
    if (p == nums.size()) {
      return;
    }
    int n = ret.size(), n2 = n + n, p1 = p + 1, v = nums[p];
    ret.resize(n2);
    for (int i = n; i < n2; ++i) {
      ret[i].reserve(p1);
      ret[i] = ret[i - n];
      ret[i].push_back(v);
    }
    subset(ret, nums, p + 1);
  }
public:
  std::vector<std::vector<int>> subsets(const std::vector<int>& nums) {
    int n = nums.size();
    if (!n) {
      return {};
    }
    int n2 = (1 << n);
    std::vector<std::vector<int>> ret;
    ret.reserve(n2);
    ret.resize(1);
    subset(ret, nums, 0);
    return ret;
  }
};
