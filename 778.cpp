#include <cassert>
#include <queue>

class Solution {
public:
  int swimInWater(std::vector<std::vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    std::vector<std::vector<int>> dist(n, std::vector<int>(m, -1));
    dist[0][0] = grid[0][0];
    std::vector<std::pair<int, int>> pq_storage;
    pq_storage.reserve(n * m);
    auto pq_compare = [&](const std::pair<int, int> & p1, const std::pair<int, int> & p2) {
      return dist[p1.first][p1.second] > dist[p2.first][p2.second];
    };
    std::priority_queue<std::pair<int, int>, decltype(pq_storage), decltype(pq_compare)> pq(pq_compare, pq_storage);
    pq.emplace(0, 0);
    auto expand = [&](int x, int y, int d) {
      if (x < 0 || x >= n || y < 0 || y >= m || dist[x][y] >= 0) {
        return;
      }
      dist[x][y] = std::max(d, grid[x][y]);
      pq.emplace(x, y);
    };
    while (!pq.empty()) {
      auto top = pq.top();
      int x = top.first, y = top.second;
      pq.pop();
      int d = dist[x][y];
      expand(x + 1, y, d);
      expand(x - 1, y, d);
      expand(x, y + 1, d);
      expand(x, y - 1, d);
      if (dist[n - 1][m - 1] != -1) {
        return dist[n - 1][m - 1];
      }
    }
    assert(false);
    return n * m;
  }
};
