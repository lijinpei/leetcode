#include <vector>

class Solution {
public:
  int canCompleteCircuit(std::vector<int> &gas, std::vector<int> &cost) {
    int n = gas.size();
    for (int p1 = 0, pn = n - 1, left = 0, owe = 0; pn >= 0; --pn) {
      int v = gas[pn] - cost[pn];
      left += v;
      owe -= v;
      if (owe <= 0) {
        while (p1 < pn) {
          int v = gas[p1] - cost[p1];
          if (v + left >= 0) {
            left += v;
            ++p1;
          } else {
            break;
          }
        }
        if (p1 == pn) {
          return p1;
        }
      }
      if (owe < 0) {
        owe = 0;
      }
    }
    return -1;
  }
};
