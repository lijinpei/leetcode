#include <vector>
#include <limits>

class Solution {
public:
  int maxProfit(std::vector<int>& prices, int fee) {
    int uh = 0;
    int h = std::numeric_limits<int>::min() / 2;
    for (auto p : prices) {
      int uh1 = std::max(uh, h + p - fee);
      h = std::max(h, uh - p);
      uh = uh1;
    }
    return uh;
  }
};
