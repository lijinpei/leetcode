#include <vector>
#include <iostream>

class Solution {
public:
  int firstMissingPositive(std::vector<int> &nums) {
    int s = nums.size();
    if (!s) {
      return 1;
    }
    auto tryFind = [&](int p) {
      int v = nums[p];
      while (v > 0 && v <= s && p + 1 != v) {
        p = v - 1;
        v = nums[p];
        nums[p] = p + 1;
      }
    };
    for (int i = 0; i < s; ++i) {
      tryFind(i);
    }
    for (int i = 0; i < s; ++i) {
      if (nums[i] != i + 1) {
        return i + 1;
      }
    }
    return s + 1;
  }
};

