#include <vector>

class Solution {
public:
  int maxProduct(std::vector<int> &nums) {
    int ans = nums[0];
    int lp = 1, ln = 0;
    for (int i = 0, s = nums.size(); i < s; ++i) {
      int v = nums[i];
      if (v > 0) {
        lp *= v;
        ln *= v;
        ans = std::max(ans, lp);
      } else if (v == 0) {
        lp = 1;
        ln = 0;
        if (ans < 0) {
          ans = 0;
        }
      } else {
        std::swap(lp, ln);
        ln *= v;
        lp *= v;
        if (lp) {
          ans = std::max(ans, lp);
        } else {
          lp = 1;
        }
      }
    }
    return ans;
  }
};
