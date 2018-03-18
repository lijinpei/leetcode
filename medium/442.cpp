#include <vector>

class Solution {
public:
  std::vector<int> findDuplicates(std::vector<int> &nums) {
    for (auto &n : nums) {
      --n;
    }
    std::vector<int> ret;
    for (int i = 0, s = nums.size(); i < s; ++i) {
      int p = nums[i];
      nums[i] = -1;
      while (-1 != nums[p]) {
        if (nums[p] == p) {
          ret.push_back(p + 1);
          nums[p] = -1;
          break;
        }
        std::swap(p, nums[p]);
      }
      nums[p] = p;
    }
    return ret;
  }
};
