#include <vector>
#include <cassert>
#include <iostream>
#include <cstdint>

class Solution {
public:
  int splitArray(std::vector<int>& nums, int m) {
    int s = nums.size();
    auto OK = [&](int64_t v) -> bool {
      int m1 = 0;
      int64_t sum = 0;
      for (int i = 0; i < s; ++i) {
        int n = nums[i];
        sum += n;
        if (sum > v) {
          ++m1;
          if (m1 == m) {
            return false;
          }
          sum = n;
        }
      }
      return true;
    };
    int64_t v1 = 0, v2 = 0;
    for (auto v : nums) {
      v2 += v;
      v1 = std::max<int64_t>(v1, v);
    }
    while (v1 < v2) {
//      assert(v1 + v2 > 0);
      long long nv = (v1 + v2) / 2;
      if (OK(nv)) {
        v2 = nv;
      } else {
        v1 = nv + 1;
      }
    }
    return v2;
  }
};

int main() {
  Solution sol;
  std::vector<int> input{1, 2147483647};
  auto ret = sol.splitArray(input, 2);
  std::cout << ret << std::endl;
}
