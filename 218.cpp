#include <queue>
#include <vector>
#include <limits>
#include <utility>

class Solution {
public:
  std::vector<std::pair<int, int>>
  getSkyline(std::vector<std::vector<int>> &buildings) {
    int n = buildings.size();
    std::vector<std::pair<int, int>> pq_storage;
    pq_storage.reserve(n);
    auto my_compare = [](const std::pair<int, int> &p1,
                         const std::pair<int, int> &p2) {
      return p1.first < p2.first;
    };
    std::priority_queue<std::pair<int, int>, decltype(pq_storage),
                        decltype(my_compare)>
        pq(my_compare, pq_storage);
    std::vector<std::pair<int, int>> ret;
    ret.reserve(2 * n);
    int xr = std::numeric_limits<int>::max(), y = 0, i = 0;
    while (i != n || !pq.empty()) {
again:
      for (; i != n; ++i) {
        if (buildings[i][0] > xr) {
          break;
        }
        if (buildings[i][2] > y) {
          int x = buildings[i][0];
          for (; i != n; ++i) {
            if (buildings[i][0] != x) {
              break;
            }
            int ny = buildings[i][2];
            int nxr = buildings[i][1];
            if (ny > y) {
              xr = nxr;
              y = ny;
            }
            pq.emplace(ny, nxr);
          }
          ret.emplace_back(x, y);
          goto again;
        } else {
            pq.emplace(buildings[i][2], buildings[i][1]);
        }
      }
      while (!pq.empty()) {
        auto & top = pq.top();
        if (top.second <= xr) {
          pq.pop();
          continue;
        }
        if (top.first < y) {
          y = top.first;
          ret.emplace_back(xr, y);
          xr = top.second;
          goto again;
        } else if (top.first == y) {
          if (top.second > xr) {
            xr = top.second;
            goto again;
          }
          pq.pop();
        }
      }
      ret.emplace_back(xr, 0);
      xr = std::numeric_limits<int>::max();
      y = 0;
    }
    return ret;
  }
};

int main() {
  Solution sol;
  std::vector<std::vector<int>> input{{0, 2, 3}, {2, 4, 3}, {4, 6, 3}};
  sol.getSkyline(input);
}
