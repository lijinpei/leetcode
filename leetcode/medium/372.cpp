#include <vector>
#include <cstdint>

class Solution {
public:
  int superPow(int a, std::vector<int> &b) {
    int s = b.size(), s1 = 0;
    auto div2 = [&]() {
      int rem = 0;
      for (int i = s1; i < s; ++i) {
        int v1 = rem * 10 + b[i];
        b[i] = v1 / 2;
        rem = v1 % 2;
      }
      for (; s1 < s && !b[s1]; ++s1) {
        continue;
      }
    };
    int ret = 1, mod = 1337;
    a %= mod;
    while (s1 != s) {
      if (b[s - 1] & 1) {
        ret = ret * a % mod;
      }
      a = a * a % mod;
      div2();
    }
    return ret;
  }
};
