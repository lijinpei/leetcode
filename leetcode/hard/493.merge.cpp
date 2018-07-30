#include <vector>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>
#include <algorithm>

class Solution {
  static std::pair<int, bool> mergeSort(int* b, int* e, int* t) {
    if  (b + 1 == e) {
      return std::make_pair(0, false);
    }
    size_t s = (e - b) / 2;
    int* m = b + s;
    int* tm = t + s;
    auto ret1 = mergeSort(b, m, t);
    auto ret2 = mergeSort(m, e, tm);
    int *b1 = ret1.second ? t : b, *e1 = b1 + s;
    int *b2 = ret2.second ? tm : m, *e2 = b2 + (e - m);
    int ret_v = ret1.first + ret2.first;
    for (int *i = b1, *j = b2; i < e1; ++i) {
      int v = *i;
      if (0 == v) {
        v = -1;
      } else if (v > 0) {
        v = (v - 1) / 2;
      } else {
        v = v / 2 - 1;
      }
      while (j < e2 && *j <= v) {
        ++j;
      }
      ret_v += j - b2;
      //std::cout << *b1 << ' ' << *(e2 - 1) << ' ' << j - b2 << std::endl;
    }
    bool ret_b = !ret1.second;
    int* ntm = ret1.second ? b : t;
    std::merge(b1, e1, b2, e2, ntm);
    return std::make_pair(ret_v, ret_b);
  }
public:
  int reversePairs(std::vector<int> &nums) {
    if (!nums.size()) {
      return 0;
    }
    std::vector<int> tmp(nums.size());
    return mergeSort(nums.data(), nums.data() + nums.size(), tmp.data()).first;
  }
};

int main() {
  Solution sol;
  std::vector<int> input(50000);
  std::iota(input.begin(), input.end(), 0);
  std::vector<int> input1{1, 3, 2, 3, 1};
  std::cout << sol.reversePairs(input1);
}
