#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <iterator>

unsigned int LOWBIT(unsigned int v) {
  return v & -int(v);
}

using T = std::pair<int, int>;
bool env_comp(const T & v1, const T & v2) {
  return v1.first < v2.first || (v1.first == v2.first && v1.second > v2.second);
}

class Solution {
public:
  int maxEnvelopes(std::vector<T> & envelopes) {
    int s = envelopes.size();
    std::sort(envelopes.begin(), envelopes.end(), env_comp);
    /*
    for (const auto & v : envelopes) {
      std::cout << v.first << ' ' << v.second << '\n';
    }
    std::cerr << "finish envelopes\n";
    */
    std::vector<int> vals(s);
    for (int i = 0; i < s; ++i) {
      vals[i] = envelopes[i].second;
    }
    std::sort(vals.begin(), vals.end());
    /*
    for (auto v : vals) {
      std::cout << v << ' ';
    }
    std::cerr << "\nfinish vals\n";
    */
    int ns = std::distance(vals.begin(), std::unique(vals.begin(), vals.end()));
    vals.resize(ns);
    /*
    for (auto v : vals) {
      std::cout << v << ' ';
    }
    std::cerr << "\nfinish vals\n";
    */
    std::vector<int> bit(ns + 1, 0);
    int ans = 0;
    auto range_max = [&](unsigned int p) {
      int ret = 0;
      while (p) {
        ret = std::max(ret, bit[p]);
        p -= LOWBIT(p);
      }
      return ret;
    };
    auto mark = [&](unsigned int p, int v) {
      while (p <= ns) {
        bit[p] = std::max(bit[p], v);
        p += LOWBIT(p);
      }
    };
    for (const auto & v : envelopes) {
      int vp = std::distance(vals.begin(), std::lower_bound(vals.begin(), vals.end(), v.second));
      int nv = range_max(vp) + 1;
      if (nv > ans) {
        ans = nv;
      }
      mark(vp + 1, nv);
    }
    return ans;
  }
};

int main() {
  Solution sol;
  std::vector<T> inputs{{1, 2}, {2, 3}, {3, 4}, {3, 5}, {4, 5}, {5, 5}, {5, 6}, {6, 7}, {7, 8}};
  auto ret = sol.maxEnvelopes(inputs);
  std::cout << ret << std::endl;
}
