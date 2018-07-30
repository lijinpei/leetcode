#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

class Solution {
  static uint32_t lowbits(uint32_t v) {
    return v & -v;
  }
public:
  std::vector<int> countSmaller(std::vector<int> &nums) {
    int n = nums.size();
    std::vector<int> nums1 = nums;
    std::sort(nums1.begin(), nums1.end());
    int n1 =
        std::distance(nums1.begin(), std::unique(nums1.begin(), nums1.end()));
    nums1.resize(n1);
    std::vector<int> bit(n1 + 1);
    auto sum = [&](uint32_t p) {
      int ret = 0;
      while (p) {
        ret += bit[p];
        p -= lowbits(p);
      }
      return ret;
    };
    auto inc = [&](uint32_t p) {
      while (p <= uint32_t(n1)) {
        bit[p] += 1;
        p += lowbits(p);
      }
    };
    std::vector<int> ret(n);
    for (int i = n - 1; i >= 0; --i) {
      int v = nums[i];
      int nv = std::distance(nums1.begin(), std::lower_bound(nums1.begin(), nums1.end(), v));
      ret[i] = sum(nv);
      inc(nv + 1);
    }
    return ret;
  }
};

int main() {
  std::vector<int> input{5, 2, 6, 1};
  Solution sol;
  auto ret = sol.countSmaller(input);
  for (auto v : ret) {
    std::cout << v << ' ';
  }
  std::cout << std::endl;
}
