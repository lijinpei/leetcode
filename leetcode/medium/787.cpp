#include <queue>
#include <vector>
#include <limits>

class Solution {
public:
  int findCheapestPrice(int n, std::vector<std::vector<int>> &flights, int src,
                        int dst, int K) {
    std::vector<int> dist(n, -1);
    std::vector<int> dist1(n, -1);
    dist[src] = 0;
    K += 1;
    while (K--) {
      for (const auto & e : flights) {
        int v = dist[e[0]];
        if (v < 0) {
          continue;
        }
        v += e[2];
        if (dist1[e[1]] < 0 || dist1[e[1]] > v) {
          dist1[e[1]] = v;
        }
      }
      dist = dist1;
    }
    return dist[dst];
  }
};
