#include <vector>

class Solution {
public:
  int arrayNesting(std::vector<int> &nums) {
    int n = nums.size();
    int ans = 1;
    for (int i = 0; i < n; ++i) {
      int v = i;
      int ans1 = 0;
      while (true) {
        int nv = nums[v];
        if (nv == v) {
          break;
        } else {
          ++ans1;
          nums[v] = v;
          v = nv;
        }
      }
      ans = std::max(ans, ans1);
    }
    return ans;
  }
};

