#include <vector>

class Solution {
public:
  std::vector<int> singleNumber(std::vector<int> &nums) {
    int v = 0;
    for (auto n : nums) {
      v ^= n;
    }
    int v1 = 1;
    while (!(v1 & v)) {
      v1 <<= 1;
    }
    int v2 = 0, v3 = 0;
    for (auto n : nums) {
      if (n & v1) {
        v2 ^= n;
      } else {
        v3 ^= n;
      }
    }
    return {v2, v3};
  }
};
