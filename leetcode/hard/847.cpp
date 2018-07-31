#include <limits>
#include <vector>
#include <utility>

class Solution {
public:
  int shortestPathLength(std::vector<std::vector<int>> &graph) {
    int N = graph.size();
    std::vector<std::vector<int>> dp(
        N, std::vector<int>(1 << N, std::numeric_limits<int>::max()));
    std::vector<std::pair<int, unsigned>> queue(N * (1 << N));
    int head = 0, tail = 0;
    for (int i = 0; i < N; ++i) {
      dp[i][1 << i] = 0;
      queue[tail++] = std::make_pair(i, unsigned(1 << i));
    }
    while (head < tail) {
      int n = queue[head].first;
      unsigned m = queue[head++].second;
      int v = dp[n][m] + 1;
      for (int i : graph[n]) {
        unsigned m1 = m | (1 << i);
        if (v < dp[i][m1]) {
          dp[i][m1] = v;
          queue[tail++] = {i, m1};
        }
      }
    }
    int ans = std::numeric_limits<int>::max();
    for (int i = 0; i < N; ++i) {
      int v = dp[i][(1 << N) - 1];
      if (v < ans) {
        ans = v;
      }
    }
    return ans;
  }
};
