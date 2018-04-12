#include <iostream>
#include <cstdlib>
#include <vector>

class Solution {
  bool calc(std::vector<double> & nums, int n) {
    if (n == 1) {
      return std::abs(nums[0] - 24) < 0.001;
    }
    for (int i = 0; i < n; ++i) {
      double v1 = nums[i];
      for (int j = i + 1; j < n; ++j) {
        double v2 = nums[j];
        nums[j] = nums[n - 1];
        nums[i] = v1 + v2;
        if (calc(nums, n - 1)) {
          return true;
        }
        nums[i] = v1 - v2;
        if (calc(nums, n - 1)) {
          return true;
        }
        nums[i] = v2 - v1;
        if (calc(nums, n - 1)) {
          return true;
        }
        nums[i] = v1 * v2;
        if (calc(nums, n - 1)) {
          return true;
        }
        if (v1 != 0) {
          nums[i] = v2 / v1;
          if (calc(nums, n - 1)) {
            return true;
          }
        }
        if (v2 != 0) {
          nums[i] = v1 / v2;
          if (calc(nums, n - 1)) {
            return true;
          }
        }
        nums[j] = v2;
      }
      nums[i] = v1;
    }
    return false;
  }
public:
  bool judgePoint24(std::vector<int> &nums_) {
    std::vector<double> nums(4);
    nums[0] = nums_[0];
    nums[1] = nums_[1];
    nums[2] = nums_[2];
    nums[3] = nums_[3];
    return calc(nums, 4);
  }
};

int main() {
  std::vector<int> input{3, 3, 8, 8};
  Solution sol;
  std::cout << sol.judgePoint24(input);
}
