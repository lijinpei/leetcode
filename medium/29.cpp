#include <iostream>
#include <climits>
#include <cstdint>

class Solution {
public:
  int divide(int64_t dividend, int64_t divisor) {
    if (0 == divisor) {
      return INT_MAX;
    }
    if (dividend == INT_MIN && divisor == -1) {
      return INT_MAX;
    }
    bool neg = false;
    if (dividend < 0) {
      neg  = true;
      dividend = -dividend;
    }
    if (divisor < 0) {
      neg = !neg;
      divisor = -divisor;
    }
    int k = 0;
    for (int64_t d = divisor; d + INT_MIN <= 0; d <<= 1) {
      ++k;
    }
    --k;
    int64_t d = int64_t(1) << k, ret = 0;
    divisor <<= k;
    while (d) {
      if (dividend >= divisor) {
        dividend -= divisor;
        ret += d;
      }
      d >>= 1;
      divisor >>= 1;
    }
    return neg ? -ret : ret;
  }
};

int main() {
  Solution sol;
  auto ret = sol.divide(-2147483648, -1);
//  auto ret = sol.divide(0, 1);
  std::cout << ret << std::endl;
}
