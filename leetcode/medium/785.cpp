#include <vector>
#include <utility>
#include <cstdint>
#include <cassert>

class Solution {
public:
  bool isBipartite(std::vector<std::vector<int>> &graph) {
    int n = graph.size();
    if (n <= 2) {
      return true;
    }
    std::vector<int8_t> color(n);
    std::vector<int> queue(n);
    int head = 0, tail = 0;
    for (int i = 0; i < n; ++i) {
      if (color[i]) {
        continue;
      }
      color[i] = 1;
      queue[tail++] = i;
      while (head < tail) {
        int n = queue[head++];
        int8_t c = color[n];
        for (auto nb : graph[n]) {
          auto & c1 = color[nb];
          if (!c1) {
            c1 = -c;
            queue[tail++] = nb;
          } else if (c1 == c) {
            return false;
          }
        }
      }
      if (tail == n) {
        return true;
      }
    }
    assert(false);
    return true;
  }
};
