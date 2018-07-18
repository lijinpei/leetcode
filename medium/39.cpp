#include <vector>

class Solution {
  class SolutionImpl {
    const std::vector<int> &candidates;
    int target, n;
    std::vector<std::vector<int>> dp, ret;
    void calc(int m, int target, int reserve) {
      if (!target) {
        ret.resize(ret.size() + 1);
        ret.back().reserve(reserve);
        return;
      }
      if (m == 0) {
        return;
      }
      for (int v = candidates[m - 1], nv = 0; target >= 0; target -= v, nv++) {
        int n1 = ret.size();
        calc(m - 1, target, reserve + nv);
        int n2 = ret.size();
        for (int i = n1; i < n2; ++i) {
          for (int j = 0; j < nv; ++j) {
            ret[i].push_back(v);
          }
        }
      }
    }

  public:
    SolutionImpl(const std::vector<int> &candidates, int target)
        : candidates(candidates), target(target), n(candidates.size()), dp(n) {}
    std::vector<std::vector<int>> calc() {
      calc(n, target, 0);
      return ret;
    }
  };

public:
  std::vector<std::vector<int>>
  combinationSum(const std::vector<int> &candidates, int target) {
    return SolutionImpl(candidates, target).calc();
  }
};
