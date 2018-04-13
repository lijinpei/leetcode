#include <numeric>
#include <vector>

class Solution {
public:
  int findMinMoves(std::vector<int> &machines) {
    int n = machines.size();
    if (n <= 1) {
      return 0;
    }
    int sum = std::accumulate(machines.begin(), machines.end(), 0);
    int average = sum / n;
    if (average * n != sum) {
      return -1;
    }
    int ans = 0, d = 0;
    for (auto m : machines) {
      int d1 = m - average;
      d = d + d1;
      ans = std::max(std::max(ans, d >= 0 ? d : -d), d1);
    }
    return ans;
  }
};

