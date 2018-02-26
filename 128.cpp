#include <unordered_set>
#include <climits>
#include <vector>

class Solution {
public:
  int longestConsecutive(std::vector<int> &nums) {
    std::unordered_set<int> uset(nums.begin(), nums.end());
    int ans = 0;
    for (auto v : uset) {
      if (uset.find(v - 1) != uset.end()) {
        continue;
      }
      bool d = false;
      int v1 = v + 1;
      while (true) {
        if (v1 == INT_MIN) {
          v1 = INT_MAX;
          d = true;
          break;
        }
        if (uset.find(v1) != uset.end()) {
          ++v1;
        } else {
          break;
        }
      }
      ans = std::max(ans, d ? v1 - v + 1 : v1 - v);
    }
    return ans;
  }
};
