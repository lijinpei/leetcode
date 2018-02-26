#include <vector>

class Solution {
public:
  int trap(std::vector<int> &height) {
    int level = 0, l = 0, r = height.size()  - 1, ans = 0;
    while (l <= r) {
      int low = (height[l] < height[r] ? height[l++] : height[r--]);
      if (low > level) {
        level = low;
      }
      ans += level - low;
    }
    return ans;
  }
};

