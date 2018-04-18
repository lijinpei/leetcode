#include <vector>
#include <algorithm>

class Solution {
public:
  int minSubArrayLen(int s, std::vector<int> &nums) {
    int n = nums.size();
    if (!n) {
      return 0;
    }
    int i0 = 0, i1 = 0, sum = 0, ans = n + 1;
    while (i1 < n) {
      while (sum < s && i1 < n) {
          sum += nums[i1++];
      }
      if (sum < s) {
        break;
      }
      while (i0 < i1 && sum - nums[i0] >= s) {
        sum -= nums[i0++];
      }
      ans = std::min(ans, i1 - i0);
      sum -= nums[i0++];
    }
    return ans == n + 1 ? 0 : ans;
  }
};
