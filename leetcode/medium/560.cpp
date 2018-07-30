#include <unordered_map>
#include <vector>

class Solution {
public:
  int subarraySum(std::vector<int> &nums, int k) {
    std::unordered_map<int, int> count;
    count[0] = 1;
    int ans = 0, sum = 0;
    for (auto v : nums) {
      sum += v;
      int nv = sum - k;
      auto itor = count.find(nv);
      if (itor != count.end()) {
        ans += itor->second;
      }
      ++count[sum];
    }
    return ans;
  }
};
