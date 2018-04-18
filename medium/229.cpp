#include <iostream>
#include <vector>
#include <limits>

class Solution {
public:
  std::vector<int> majorityElement(std::vector<int> &nums) {
    if (!nums.size()) {
      return {};
    }
    // the initial value of v1/v2 doesn't matter, as long as they differ.
    int v1, v2 = v1 + 1;
    // n1 is the +/- number of v1 in some sequence, except v2
    // n2 is the +/- number of v1 in some sequence, except v1
    int n1 = 0, n2 = 0;
    for (auto v : nums) {
      if (v == v1) {
        ++n1;
      } else if (v == v2) {
        ++n2;
      } else if (!n1) {
        v1 = v;
        n1 = 1;
      } else if (!n2) {
        v2 = v;
        n2 = 1;
      } else {
        --n1;
        --n2;
      }
    }
    n1 = n2 = 0;
    for (auto v : nums) {
      if (v == v1) {
        ++n1;
      }
      if (v == v2) {
        ++n2;
      }
    }
    int n = nums.size() / 3;
    if (n1 > n && n2 > n) {
      return {v1, v2};
    } else if (n1 > n) {
      return {v1};
    } else if (n2 > n) {
      return {v2};
    } else {
      return {};
    }
  }
};
