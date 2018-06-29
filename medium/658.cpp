#include <vector>
#include <algorithm>

class Solution {
public:
  std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x) {
    std::vector<int> ret(k);
    auto p1 = std::lower_bound(arr.begin(), arr.end(), x);
    auto p2 = p1;
    for (int i = k; i; --i) {
      if (p2 == arr.begin()) {
        p1 += i;
        break;
      }
      if (p1 == arr.end()) {
        p2 -= i;
        break;
      }
      int v2 = *(p2 - 1);
      int v1 = *p1;
      if (x - v2 <= v1 - x) {
        --p2;
      } else {
        ++p1;
      }
    }
    std::copy(p2, p1, ret.begin());
    return ret;
  }
};
