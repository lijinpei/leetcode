#include <algorithm>
#include <vector>

class Solution {
public:
  int findLongestChain(std::vector<std::vector<int>> &pairs) {
    if (pairs.empty()) {
      return 0;
    }
    std::sort(pairs.begin(), pairs.end(),
              [](const std::vector<int> &p1, const std::vector<int> &p2) {
                return p1[1] < p2[1];
              });
    int p = 1, n = 1, s = pairs.size(), pe = pairs[0][1];
    while (true) {
      for (; p < s && pairs[p][0] <= pe; ++p) {
      }
      if (p == s) {
        break;
      }
      ++n;
      pe = pairs[p++][1];
    }
    return n;
  }
};
