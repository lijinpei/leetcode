#include <vector>
#include <algorithm>

class Solution {
public:
  int hIndex(std::vector<int> &citations) {
    std::sort(citations.begin(), citations.end());
    int n = citations.size(), ans = 0;
    for (int i = n - 1; i >= 0; --i) {
      int nv = std::min(citations[i], n - i);
      if (nv > ans) {
        ans = nv;
      }
      if (ans >= citations[i]) {
        break;
      }
    }
    return ans;
  }
};
