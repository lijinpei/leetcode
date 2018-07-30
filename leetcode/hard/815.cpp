#include <vector>
#include <forward_list>
#include <unordered_map>

class Solution {
  static const int NMAX = 500;
public:
  int numBusesToDestination(std::vector<std::vector<int>>& routes, int S, int T) {
    if (S == T) {
      return 0;
    }
    int N = 0;
    std::unordered_map<int, int> map;
    for (auto & r : routes) {
      for (auto &s : r) {
        auto & m = map[s];
        if (!m) {
          m = ++N;
        }
        s = m;
      }
    }
    {
      auto s = map[S];
      if (!s) {
        return -1;
      }
      S = s;
      auto t = map[T];
      if (!t) {
        return -1;
      }
      T = t;
    }
    std::vector<int> dist(N + 1);
    std::vector<std::forward_list<int>> buses(N + 1);
    std::vector<int> queue(N);
    for (int i = 0, rs = routes.size(); i < rs; ++i) {
      for (auto s : routes[i]) {
        buses[s].push_front(i);
      }
    }
    int n = routes.size();
    std::vector<bool> to_T(n);
    std::vector<bool> has_taken(n);
    for (auto v : buses[T]) {
      to_T[v] = true;
    }
    int head = 0, tail = 1;
    queue[0] = S;
    dist[S] = 1;
    while (head < tail) {
      int n = queue[head++];
      int d = dist[n];
      int d1 = d + 1;
      for (auto b : buses[n]) {
        if (to_T[b]) {
          return d;
        }
        if (has_taken[b]) {
          continue;
        }
        has_taken[b] = true;
        for (auto s : routes[b]) {
          if (!dist[s]) {
            dist[s] = d1;
            queue[tail++] = s;
          }
        }
      }
    }
    return -1;
  }
};
