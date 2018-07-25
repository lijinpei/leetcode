#include <vector>

class Solution {
  /*
  static int calc(std::vector<int> & father, int n) {
    if (!father[n]) {
      return n;
    }
    return father[n] = calc(father, father[n]);
  }
  */
public:
  std::vector<int>
  findRedundantConnection(std::vector<std::vector<int>> &edges) {
    int n = edges.size();
    std::vector<int> father(n + 1);
    auto calc = [&](int n) {
      int n0 = n;
      while (father[n]) {
        n = father[n];
      }
      while (father[n0]) {
        int n1 = father[n0];
        father[n0] = n;
        n0 = n1;
      }
      return n;
    };
    for (auto & e : edges) {
      int f1 = calc(e[0]);
      int f2 = calc(e[1]);
      if (f1 == f2) {
        return e;
      }
      father[f1] = f2;
    }
  }
};
