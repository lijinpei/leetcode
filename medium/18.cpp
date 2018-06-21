#include <algorithm>
#include <vector>

class Solution {
public:
  std::vector<std::vector<int>> fourSum(std::vector<int> &nums, int target) {
    std::vector<std::vector<int>> ret;
    int n = nums.size();
    if (n < 4) {
      return ret;
    }
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < n - 3; ++i) {
      int v1 = nums[i];
      int s1 = v1;
      for (int j = i + 1; j < n - 2; ++j) {
        int v2 = nums[j];
        int s2 = s1 + v2;
        int k1 = n - 1;
        for (int k = j + 1; k < n - 1; ++k) {
          int v3 = nums[k];
          int s3 = s2 + v3;
          while (k1 > k && s3 + nums[k1] > target) {
            --k1;
          }
          if (k1 <= k) {
            break;
          }
          int v4 = nums[k1];
          if (s3 + v4 != target) {
            continue;
          }
          std::vector<int> nv{v1, v2, v3, v4};
          if (ret.empty() || nv > ret.back()) {
            ret.push_back(std::move(nv));
          }
        }
      }
    }
    return ret;
  }
};
