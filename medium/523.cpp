#include <vector>
#include <limits>
#include <cstdint>
#include <map>
#include <utility>

class Solution {
public:
  bool checkSubarraySum(std::vector<int> &nums, int k) {
    k = k < 0 ? -k : k;
    if (k > std::numeric_limits<int32_t>::max()) {
      return false;
    }
    if (!k) {
      int c = 0;
      for (auto v : nums) {
        if (!v) {
          ++c;
        } else {
          c = 0;
        }
        if (c >= 2) {
          return true;
        }
      }
      return false;
    }
    std::map<int, bool> has;
    int n = nums.size();
    if (n <= 1) {
      return false;
    }
    int s = nums[0] % k;
    bool* ps = &has[s];
    for (int i = 1; i < n; ++i) {
      int s1 = (s + nums[i]) % k;
      bool *ps1 = &has[s1];
      if (!s1 || *ps1) {
        return true;
      }
      *ps = true;
      ps = ps1;
      s = s1;
    }
    return false;
  }
};
