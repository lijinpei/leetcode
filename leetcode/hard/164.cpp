#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
public:
  int maximumGap(std::vector<int> &nums) {
    int s = nums.size();
    if (s < 2) {
      return 0;
    }
    const int BNUM = 8;
    const int BMAX = 1 << BNUM;
    const int BROUND = 32 / BNUM;
    std::vector<int> count(BMAX, 0);
    std::vector<int> nums1(s);
    for (int r = 0; r < BROUND; ++r) {
      for (int i = 0; i < s; ++i) {
        ++count[(nums[i] >> (BNUM * r)) & (BMAX - 1)];
      }
      int s = count[0];
      count[0] = 0;
      for (int i = 1; i < BMAX; ++i) {
        int s1 = s;
        s += count[i];
        count[i] = s1;
      }
      for (int i = 0; i < s; ++i) {
        nums1[count[(nums[i] >> (BNUM * r)) & (BMAX - 1)]++] = nums[i];
      }
      if (r + 1 != BROUND) {
        std::fill(count.begin(), count.end(), 0);
      }
      std::swap(nums, nums1);
    }
    int ans = nums[1] - nums[0];
    for (int i = 2; i < s; ++i) {
      int nv = nums[i] - nums[i - 1];
      ans = std::max(ans, nv);
    }
    return ans;
  }
};

int main() {
  Solution sol;
  std::vector<int> input{4, 8, 3};
  auto ret = sol.maximumGap(input);
  std::cout << ret << std::endl;
}

