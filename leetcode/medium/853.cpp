#include <vector>
#include <utility>
#include <algorithm>

class Solution {
public:
  int carFleet(int target, std::vector<int> &position, std::vector<int> &speed) {
    int n = position.size();
    if (!n) {
      return 0;
    }
    std::vector<std::pair<int, int>> vp(n);
    for (int i = 0; i < n; ++i) {
      vp[i].first = speed[i];
      vp[i].second = target- position[i];
    }
    std::sort(vp.begin(), vp.end(), [](const std::pair<int, int> & vp1, const std::pair<int, int> & vp2) {
              return vp1.second < vp2.second;
              });
    auto my_comp = [](int v1, int d1, int v2, int d2) {
      return int64_t(d1) * v2 >= int64_t(d2) * v1;
    };
    int ans = n;
    int v1 = vp[0].first;
    int d1 = vp[0].second;
    for (int i = 1; i < n; ++i) {
      int v2 = vp[i].first;
      int d2 = vp[i].second;
      if (my_comp(v1, d1, v2, d2)) {
        --ans;
      } else {
        v1 = v2;
        d1 = d2;
      }
    }
    return ans;
  }
};
