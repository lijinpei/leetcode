#include <algorithm>
#include <vector>

class Solution {
public:
  double champagneTower(int poured, int query_row, int query_glass) {
    std::vector<double> glass(query_row + 1);
    glass[0] = poured;
    bool has_over = poured > 1;
    int i = 1;
    auto f = [](double g) -> double {
      return std::max<double>(g - 1, 0) * 0.5;
    };
    for (; has_over && i <= query_row; ++i) {
      has_over = false;
      double d = f(glass[0]);
      glass[0] = d;
      if (d > 1) {
        has_over = true;
      }
      for (int j = 1; j < i; ++j) {
        double d1 = f(glass[j]);
        double nv = d + d1;
        if (nv > 1) {
          has_over = true;
        }
        glass[j] = nv;
        d = d1;
      }
      glass[i] = d;
    }
    if (i > query_row) {
      return std::min<double>(glass[query_glass], 1);
    }
    return 0;
  }
};
