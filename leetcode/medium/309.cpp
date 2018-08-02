#include <vector>
#include <limits>

class Solution {
public:
  int maxProfit(std::vector<int> &prices) {
    int uh0 = 0, uh1 = 0;
    int h = std::numeric_limits<int>::min();
    for (auto p : prices) {
      int uh0_ = std::max(uh0, uh1);
      uh1 = h + p;
      h = std::max(uh0 - p, h);
      uh0 = uh0_;
    }
    return std::max(uh0, uh1);
  }
};
