#include <iostream>
#include <utility>
#include <vector>

class Solution {
  int ans_v;
  std::vector<int> En;
  std::vector<int> D;
  std::vector<int> E;
  std::vector<int> Ep;
  std::vector<int> Lp;
  std::vector<int> Lv;
  std::vector<int> Ld;
  int N;
  int dfs(int n, int d) {
    D[n] = d;
    int lv1 = 0, lv2 = 0, lp1 = -1;
    auto update = [&](int l, int c) {
      if (l >= lv1) {
        lv2 = lv1;
        lv1 = l;
        lp1 = c;
      } else if (l >= lv2) {
        lv2 = l;
      }
    };
    int ep = Ep[n];
    int ret = 0;
    for (int i = 0, i1 = En[n]; i < i1; ++i) {
      int c = E[ep + i];
      if (!D[c]) {
        int nv = dfs(c, d + 1);
        if (nv > ret) {
          ret = nv;
        }
        update(nv, c);
      }
    }
    int nv = lv1 + lv2 + 1;
    Lp[n] = lp1;
    Lv[n] = nv;
    if (nv > ans_v) {
      ans_v = nv;
    }
    return Ld[n] = ret + 1;
  }
public:
  std::vector<int> findMinHeightTrees(int n,
                                      std::vector<std::pair<int, int>> &edges) {
    N = n;
    int m = edges.size();
    D.clear();
    D.resize(n);
    En.clear();
    En.resize(n);
    E.clear();
    E.resize(m + m);
    Ep.clear();
    Ep.resize(n);
    Lp.clear();
    Lp.resize(n);
    Lv.clear();
    Lv.resize(n);
    Ld.clear();
    Ld.resize(n);
    for (auto e : edges) {
      ++En[e.first];
      ++En[e.second];
    }
    for (int i = 0, s = 0; i < n; ++i) {
      s += En[i];
      Ep[i] = s;
    }
    for (auto e : edges) {
      E[--Ep[e.first]] = e.second;
      E[--Ep[e.second]] = e.first;
    }
    ans_v = 0;
    dfs(0, 1);
    int p = 0;
    while (Lv[p] != ans_v) {
      p = Lp[p];
    }
    int td = (ans_v / 2) + 1;
    while (Ld[p] != td) {
      p = Lp[p];
    }
    if (ans_v & 1) {
      return {p};
    } else {
      return {p, Lp[p]};
    }
  }
};

int main() {
  Solution sol;
  std::vector<std::pair<int, int>> E{{1,0},{1,2},{1,3}};
  auto ret = sol.findMinHeightTrees(4, E);
  for (auto v : ret) {
    std::cout << v << ' ';
  }
  std::cout << std::endl;
}
