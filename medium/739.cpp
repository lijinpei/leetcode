#include <vector>
#include <utility>

class Solution {
public:
  std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
    int n = temperatures.size();
    if (!n) {
      return {};
    }
    std::vector<std::pair<int, int>> stack(n);
    std::vector<int> ret(n);
    int tos = -1;
    for (int i = n - 1; i >= 0; --i) {
      int t = temperatures[i];
      while (tos >= 0 && t >= stack[tos].first) {
        --tos;
      }
      ret[i] = tos >= 0 ? stack[tos].second - i : 0;
      stack[++tos] = {t, i};
    }
    return ret;
  }
};
