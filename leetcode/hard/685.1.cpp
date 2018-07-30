#include <vector>
#include <iostream>

class Solution {
  int n;
  std::vector<int> ancestor;
public:
  std::vector<int> findRedundantDirectedConnection(std::vector<std::vector<int>> const &edges) {
    n = edges.size();
    std::vector<int> ancestor(n + 1, 0);
    std::vector<int> st(n);
    auto find_ancestor = [&](int v) {
      int s = 0, a = ancestor[v];
      while (a) {
        st[s++] = v;
        v = a;
        a = ancestor[v];
      }
      for (int i = 0; i < s; ++i) {
        ancestor[st[i]] = v;
      }
      return v;
    };
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
        ancestor[a1] = a2;
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
