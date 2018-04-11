#include <vector>

class Solution {
public:
  int singleNonDuplicate(std::vector<int>& nums) {
    int n = nums.size();
    if (n == 1) {
      return nums[0];
    }
    if (nums[0] != nums[1]) {
      return nums[0];
    }
    n = (n >> 1) + 1;
    int l = -1;
    while (l + 1 != n) {
      int m = (l + n) >> 1;
      if (nums[m << 1] == nums[(m << 1) + 1]) {
        l = m;
      } else {
        n = m;
      }
    }
    return nums[2 * n];
  }
};
