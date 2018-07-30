#include <vector>

class Solution {
public:
  int jump(std::vector<int> &nums) {
    int s = nums.size(), p = 0, np = 0, np1 = 0, j = 0;
    while (np + 1 < s) {
      ++j;
      for (; p <= np; ++p) {
        int v = p + nums[p];
        if (v > np1) {
          np1 = v;
          if (np1 + 1 >= s) {
            return j;
          }
        }
      }
      np = np1;
    }
    return j;
  }
};
