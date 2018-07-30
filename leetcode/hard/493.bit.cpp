#include <cstdint>
#include <algorithm>
#include <vector>
#include <iostream>
#include <algorithm>

uint32_t LOWBIT(uint32_t v) {
  return v & -int32_t(v);
}

class Solution {
public:
  int reversePairs(const std::vector<int> &nums) {
    int s = nums.size();
    std::vector<int> BIT(s + 1);
    auto BIT_mark = [&](int p) {
      while (p <= s) {
        ++BIT[p];
        p += LOWBIT(p);
      }
    };
    auto BIT_sufffix_sum = [&](int p) {
      int ret = 0;
      while (p) {
        ret += BIT[p];
        p -= LOWBIT(p);
      }
      return ret;
    };
    std::vector<int> sorted(nums);
    std::sort(sorted.begin(), sorted.end());
    auto upper_bound = [&](int v) {
      return std::distance(sorted.begin(),
                           std::upper_bound(sorted.begin(), sorted.end(), v));
    };
    int ans = 0;
    for (int i = s - 1; i >= 0; --i) {
      int v = nums[i];
      int v1 = (v > 0) ? (v - 1) / 2 : v / 2 - 1;
      int p = upper_bound(v);
      int p1 = upper_bound(v1);
      int nv = BIT_sufffix_sum(p1);
      ans += nv;
      //std::cout << nv << std::endl;
      BIT_mark(p);
    }
    return ans;
  }
};

int main() {
  Solution sol;
  std::cout << sol.reversePairs({1, 3, 2, 3, 1}) << std::endl;
  std::cout << sol.reversePairs({2, 4, 3, 5, 1}) << std::endl;
}
