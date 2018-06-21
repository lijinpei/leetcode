#include <vector>
#include <algorithm>

class Solution {
public:
  void nextPermutation(std::vector<int> &nums) {
    int s = nums.size();
    if (s <= 1) {
      return;
    }
    int v = nums[s - 1];
    int p = s - 1;
    while (p >= 0) {
      if (nums[p] < v) {
        break;
      }
      v = nums[p--];
    }
    if (p < 0) {
      std::reverse(nums.begin(), nums.end());
      return;
    }
    v = nums[p];
    int p1 = p + 1;
    while (p1 < s && nums[p1] > v) {
      ++p1;
    }
    std::swap(nums[p],  nums[p1 - 1]);
    std::reverse(nums.begin() + p + 1, nums.end());
  }
};
