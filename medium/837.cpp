#include <vector>
#include <algorithm>

class Solution {
public:
  double new21Game(int N, int K, int W) {
    if (!K) {
      return 1;
    }
    N = std::min(N, K - 1 + W);
    std::vector<double> sum(K + 1);
    auto SUM = [&](int p2, int p1) {
      return p1 ? sum[p2] - sum[p1 - 1] : sum[p2];
    };
    double v = 1. / W;
    sum[0] = 1;
    for (int i = 1; i <= K; ++i) {
      int j = std::max(0, i - W);
      sum[i] = sum[i - 1] + SUM(i - 1, j) * v;
    }
    double ans = sum[K];
    for (int i = K + 1; i <= N; ++i) {
      int j = std::max(0, i - W);
      ans += SUM(K - 1, j) * v;
    }
    return ans;
  }
};
