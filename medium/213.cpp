#include <vector>
#include <algorithm>

class Solution {
public:
    int rob(std::vector<int>& nums) {
      int n = nums.size();
      if (!n) {
        return 0;
      }
      if (n == 1) {
        return nums[0];
      }
      if (n == 2) {
        return std::max(nums[0], nums[1]);
      }
      int v1 = 0;
      int v2 = nums[1];
      int v3 = nums[0];
      int v4 = 0;
      for (int i = 2; i < n; ++i) {
        int v = nums[i];
        int v1_ = std::max(v1, v2);
        int v2_ = v1 + v;
        int v3_ = std::max(v3, v4);
        int v4_ = v3 + v;
        v1 = v1_;
        v2 = v2_;
        v3 = v3_;
        v4 = v4_;
      }
      return std::max(std::max(v1, v2), v3);
    }
};
