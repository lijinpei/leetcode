#include <vector>

class Solution {
  class SolutionImpl {
    std::vector<std::vector<int>> ret;
    int k, n;
    void calc(int m, int t, int v) {
      if (v == 1) {
        if (t && t <= m) {
          ret.resize(ret.size() + 1);
          ret.back().reserve(k);
          ret.back().push_back(t);
        }
        return;
      }
      if (m == 0) {
        return;
      }
      calc(m - 1, t, v);
      if (m > t) {
        return;
      }
      int n1 = ret.size();
      calc(m - 1, t - m, v - 1);
      int n2 = ret.size();
      for (int i = n1; i < n2; ++i) {
        ret[i].push_back(m);
      }
    }
  public:
    SolutionImpl(int k, int n) : ret(), k(k), n(n) {
    }
    std::vector<std::vector<int>> calc() {
      calc(9, n, k);
      return std::move(ret);
    }
  };
public:
  std::vector<std::vector<int>> combinationSum3(int k, int n) {
    return SolutionImpl(k, n).calc();
  }
};
