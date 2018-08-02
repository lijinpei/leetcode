#include <vector>
#include <algorithm>

class Solution {
public:
  int deleteAndEarn(std::vector<int> &nums) {
    const int nmax = 10000;
    std::vector<int> count(nmax + 1);
    for (auto n : nums) {
      ++count[n];
    }
    int s1 = 0, s2 = 0;
    for (int i = 1; i <= nmax; ++i) {
      int n = count[i] * i;
      int s2_ = s1 + n;
      s1 = std::max(s1, s2);
      s2 = s2_;
    }
    return std::max(s1, s2);
  }
};
