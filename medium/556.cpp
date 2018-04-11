#include <algorithm>
#include <cstdint>
#include <numeric>

class Solution {
public:
  int nextGreaterElement(int n) {
    int digits[10];
    int m = 0;
    while (n) {
      digits[m++] = n % 10;
      n /= 10;
    }
    for (int i = 0; i + 1 < m; ++i) {
      if (digits[i] > digits[i + 1]) {
        int64_t ret = 0;
        int j = i;
        for (; j >= 0 && digits[j] > digits[i + 1]; --j) {
        }
        std::swap(digits[j + 1], digits[i + 1]);
        std::reverse(digits, digits + i + 1);
        for (int i = m - 1; i >= 0; --i) {
          ret = ret * 10 + digits[i];
        }
        return ret <= std::numeric_limits<int32_t>::max() ? ret : -1;
      }
    }
    return -1;
  }
};
