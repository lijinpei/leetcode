#include <vector>

class Solution {
public:
  bool isSelfCrossing(std::vector<int> &x) {
    int n = x.size();
    if (n <= 3) {
      return false;
    }
    auto test4 = [&](int p) {
      return x[p] >= x[p - 2] && x[p - 1] <= x[p - 3];
    };
    auto test5 = [&](int p) {
      return (x[p] + x[p - 4] >= x[p - 2]) && (x[p - 1] == x[p - 3]);
    };
    auto test6 = [&](int p) {
      return x[p - 4] <= x[p - 2] && x[p] + x[p - 4] >= x[p - 2] &&
             x[p - 1] <= x[p - 3] && x[p - 1] + x[p - 5] >= x[p - 3];
    };
    if (test4(3)) {
      return true;
    }
    if (n >= 5 && (test5(4) || test4(3))) {
      return true;
    }
    for (int i = 5; i < n; ++i) {
      if (test4(i) || test5(i) || test6(i)) {
        return true;
      }
    }
    return false;
  }
};
