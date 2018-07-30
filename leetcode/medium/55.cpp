#include <vector>

class Solution {
public:
  bool canJump(std::vector<int> &nums) {
    int n = nums.size();
    if (n <= 1) {
      return true;
    }
    int tp = 1;
    for (int i = 0; i < tp && tp < n; ++i) {
      tp = std::max(tp, nums[i] + i + 1);
    }
    return tp >= n;
  }
};
