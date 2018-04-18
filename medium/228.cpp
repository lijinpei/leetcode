#include <vector>
#include <string>

class Solution {
public:
  std::vector<std::string> summaryRanges(std::vector<int>& nums) {
    int n = nums.size();
    if (!n) {
      return {};
    }
    std::vector<std::string> ret;
    int lv = nums[0], lp = 0;
    for (int i = 1; i < n; ++i) {
      if (nums[i] == lv + 1) {
        ++lv;
        continue;
      }
      if (lp + 1 == i) {
        ret.push_back(std::to_string(nums[lp]));
      } else {
        ret.push_back(std::to_string(nums[lp]) + "->" + std::to_string(nums[i - 1]));
      }
      lv = nums[i];
      lp = i;
    }
    if (lp + 1 == n) {
      ret.push_back(std::to_string(lv));
    } else {
      ret.push_back(std::to_string(nums[lp]) + "->" + std::to_string(nums[n - 1]));
    }
    return ret;
  }
};
