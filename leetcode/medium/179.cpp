#include <algorithm>
#include <vector>
#include <string>

class Solution {
public:
  std::string largestNumber(std::vector<int> &nums) {
    int n = nums.size();
    std::vector<std::string> strs(n);
    int l = 0;
    for (int i = 0; i < n; ++i) {
      strs[i] = std::to_string(nums[i]);
      l += strs[i].size();
    }
    struct {
      bool operator()(const std::string s1, const std::string s2) {
        return s1 + s2 > s2 + s1;
      }
    } myCompare;
    std::sort(strs.begin(), strs.end(), myCompare);
    std::string ret;
    ret.reserve(l);
    for (const auto & s : strs) {
      ret += s;
    }
    int i = 0;
    for (; i < l; ++i) {
      if ('0' != ret[i]) {
        break;
      }
    }
    ret = ret.substr(i == l ? l - 1 : i);
    return ret;
  }
};
