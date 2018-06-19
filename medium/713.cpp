#include <vector>

class Solution {
public:
  int numSubarrayProductLessThanK(std::vector<int> &nums, int k) {
    int s = nums.size(), i = 0, ans = 0, p = 1;
    for (int j = 0; j < s; ++j) {
      p *= nums[j];
      while (p >= k && i <= j) {
        p /= nums[i++];
      }
      ans += j - i + 1;
    }
    return ans;
  }
};
