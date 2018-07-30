#include <utility>
#include <vector>
#include <limits>

class Solution {
public:
  std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size(), mn = m * n;
    std::vector<std::pair<int, int>> queue(mn);
    std::vector<std::vector<int>> dis(n, std::vector<int>(m, std::numeric_limits<int>::max()));
    int head = 0, tail = 0;
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < m; ++y) {
        if (!matrix[x][y]) {
          dis[x][y] = 0;
          queue[tail++] = {x, y};
        }
      }
    }
    auto try_visit = [&](int x, int y, int d) {
      if (x < 0 || x >= n || y < 0 || y >= m) {
        return;
      }
      auto & d0 = dis[x][y];
      if (d0 == std::numeric_limits<int>::max()) {
        d0 = d;
        queue[tail++] = {x, y};
        return;
      }
      if (d < d0) {
        d0 = d;
      }
    };
    while (head != tail) {
      int x = queue[head].first;
      int y = queue[head++].second;
      int d = dis[x][y] + 1;
      try_visit(x + 1, y, d);
      try_visit(x - 1, y, d);
      try_visit(x, y + 1, d);
      try_visit(x, y - 1, d);
    }
    return std::move(dis);
  }
};
