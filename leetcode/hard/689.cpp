#include <vector>
#include <cstdint>

class Solution {
public:
  std::vector<int> maxSumOfThreeSubarrays(std::vector<int> &nums, int k) {
    int n = nums.size();
    if (k <= 0 || n < 3 * k) {
      return {};
    }
    std::vector<int64_t> ksum(n - k + 1);
    {
      int64_t s = 0;
      for (int i = 0; i < k; ++i) {
        s += nums[i];
      }
      for (int i = 0, i1 = n - k + 1; i < i1; ++i) {
        ksum[i] = s;
        s -= nums[i];
        s += nums[i + k];
      }
    }
    std::vector<int64_t> lv1(n - k + 1);
    std::vector<int> lp1(n - k + 1);
    int64_t lv = ksum[n - k];
    int lp;
    for (int i = n - k; i >= 0; --i) {
      int nv = ksum[i];
      if (lv <= nv) {
        lv = nv;
        lp = i;
      }
      lv1[i] = lv;
      lp1[i] = lp;
    }
    std::vector<int64_t> lv2(n - 2 * k + 1);
    std::vector<int> lp2(n - 2 * k + 1);
    lv = ksum[n - 2 * k] + lv1[n - k];
    for (int i = n - 2 * k; i >= 0; --i) {
      int nv = ksum[i] + lv1[i + k];
      if (lv <= nv) {
        lv = nv;
        lp = i;
      }
      lv2[i] = lv;
      lp2[i] = lp;
    }
    std::vector<int64_t> lv3(n - 3 * k + 1);
    std::vector<int> lp3(n - 3 * k + 1);
    lv = ksum[n - 3 * k] + lv2[n - 2 * k];
    for (int i = n - 3 * k; i >= 0; --i) {
      int nv = ksum[i] + lv2[i + k];
      if (lv <= nv) {
        lv = nv;
        lp = i;
      }
      lv3[i] = lv;
      lp3[i] = lp;
    }
    return {lp3[0], lp2[lp3[0] + k], lp1[lp2[lp3[0] + k] + k]};
  }
};
