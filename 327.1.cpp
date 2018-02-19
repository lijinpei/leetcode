#include <vector>
#include <iostream>
#include <algorithm>

uint32_t LOWBIT(uint32_t v) {
  return v & -int32_t(v);
}

class Solution {
public:
  int countRangeSum(std::vector<int>& nums, int lower, int upper) {
    size_t s = nums.size();
    if (!s) {
      return 0;
    }
    std::vector<int64_t> suffix_sum(s);
    {
      int64_t sum = nums[0];
      suffix_sum[0] = sum;
      for (size_t i = 1; i < s; ++i) {
        sum += nums[i];
        suffix_sum[i] = sum;
      }
      suffix_sum[s - 1] = 0;
    }

    std::vector<int> bit(s + 1);
    auto mark_bit = [s, &bit](size_t p, int c) {
      while (p <= s) {
        bit[p] += c;
        p += LOWBIT(p);
      }
    };

    auto sum_bit = [&bit](size_t p) {
      int ret = 0;
      while (p) {
        ret += bit[p];
        p -= LOWBIT(p);
      }
      return ret;
    };

    std::sort(suffix_sum.begin(), suffix_sum.end());
    int ret = 0;
    int64_t v = 0;
    for (int i = 0; i < s; ++i) {
      size_t p = std::distance(suffix_sum.begin(), std::upper_bound(suffix_sum.begin(), suffix_sum.end(), v));
      mark_bit(p, 1);
      v += nums[i];
      int64_t low = v - upper;
      int64_t up = v - lower;
      size_t low1 = std::distance(suffix_sum.begin(), std::lower_bound(suffix_sum.begin(), suffix_sum.end(), low));
      size_t up1 = std::distance(suffix_sum.begin(), std::upper_bound(suffix_sum.begin(), suffix_sum.end(), up));
      //std::cout << low << ' ' << up << std::endl;
      //std::cout << ret << std::endl;
      ret += sum_bit(up1) - sum_bit(low1);
    }
    return ret;
  }
};

int main() {
  std::vector<int> v{-2, 5, -1};
  Solution sol;
  std::cout << sol.countRangeSum(v, -2, 2) << std::endl;
  v = {0};
  std::cout << sol.countRangeSum(v, 0, 0) << std::endl;
}

