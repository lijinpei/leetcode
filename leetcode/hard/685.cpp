#include <vector>
#include <iostream>

class Solution {
  int n;
  std::vector<int> ancestor, rank;
  int find_ancestor(int v) {
    int a = ancestor[v];
    return a ? ancestor[v] = find_ancestor(a) : v;
  }
  void merge(int v1, int v2) {
    int &r1 = rank[v1], &r2 = rank[v2];
    if (r1 < r2) {
      ancestor[v1] = v2;
    } else if (r1 > r2) {
      ancestor[v2] = v1;
    } else {
      ancestor[v1] = v2;
      ++r2;
    }
  }
public:
  std::vector<int> findRedundantDirectedConnection(std::vector<std::vector<int>> const &edges) {
    n = edges.size();
    ancestor = std::vector<int>(n + 1, 0);
    rank = std::vector<int>(n + 1, 0);
    std::vector<int> father(n + 1, 0);
    int b1 = 0, b2, b3;
    bool have_circle = false;
    int c1, c2;
    for (const auto & e : edges) {
      int v1 = e[0], v2 = e[1], &f = father[v2];
      if (f) {
        if (have_circle) {
          return {f, v2};
        }
        b1 = v2;
        b2 = f;
        b3 = v1;
        continue;
      }
      f = v1;
      int a1 = find_ancestor(v1), a2 = find_ancestor(v2);
      if (a1 == a2) {
        if (b1) {
          return {b2, b1};
        } else {
          have_circle = true;
          c1 = v1;
          c2 = v2;
        }
      } else {
        merge(a1, a2);
      }
    }
    if (have_circle) {
      return {c1, c2};
    } else {
      return {b3, b1};
    }
  }
};

int main() {
  Solution sol;
//  std::vector<std::vector<int>> input{{1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 5}};
  std::vector<std::vector<int>> input{{1, 2}, {2, 3}, {3, 1}, {4, 1}};
  auto ans = sol.findRedundantDirectedConnection(input);
  std::cout << ans[0] << ' ' << ans[1] << std::endl;
}
