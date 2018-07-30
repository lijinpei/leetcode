#include <vector>

class Solution {
public:
  int minSwapsCouples(std::vector<int> &row) {
    int n = row.size();
    if (!n) {
      return 0;
    }
    std::vector<int> index(n);
    for (int i = 0; i < n; ++i) {
      index[row[i]] = i;
    }
    int ret = 0;
    for (int i = 0; i < n; i += 2) {
      int n1 = row[i], n2 = row[i + 1];
      if ((n1 ^ n2) == 1) {
        continue;
      }
      int p1 = n1 ^ 1;
      std::swap(row[index[p1]], row[i + 1]);
      index[n2] = index[p1];
      ++ret;
    }
    return ret;
  }
};
