#include <vector>
#include <cstdint>

uint32_t LOWBITS(uint32_t v) {
  return v & -v;
}

class NumArray {
  uint32_t s;
  std::vector<int> bit, nums;
  int sum(uint32_t p) {
    int ret = 0;
    while (p) {
      ret += bit[p];
      p -= LOWBITS(p);
    }
    return ret;
  }
public:
    NumArray(const std::vector<int> & nums) : s(nums.size()), bit(s + 1), nums(s) {
      for (uint32_t i = 0; i < s; ++i) {
        update(i, nums[i]);
      }
    }
    
    void update(int i, int val) {
      int d = val - nums[i];
      uint32_t p = i + 1;
      while (p <= s) {
        bit[p] += d;
        p += LOWBITS(p);
      }
      nums[i] = val;
    }
    
    int sumRange(int i, int j) {
      return sum(j + 1) - sum(i);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */
