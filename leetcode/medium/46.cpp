#include <vector>
#include <algorithm>

class Solution {
  static int factorial(int n) {
    if (n == 1) {
      return 1;
    }
    return n * factorial(n - 1);
  }
std::vector<std::vector<int>> ret;
  int ret_p, n;
  void permute(std::vector<int> &nums, int p) {
    if (p == n) {
      ret.push_back(nums);
      return;
    }
    permute(nums, p + 1);
    for (int i = p + 1; i < n; ++i) {
      std::swap(nums[i], nums[p]);
      permute(nums, p + 1);
      std::swap(nums[i], nums[p]);
    }
  }
public:
  std::vector<std::vector<int>> permute(std::vector<int> &nums) {
    n = nums.size();
    ret_p = 0;
    ret.reserve(factorial(n));
    permute(nums, 0);
    return ret;
  }
};
