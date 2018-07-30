#include <iostream>

class Solution {
  // how many numbers are there that begin with v, and no greater than n
  static int64_t smaller(int64_t v, int64_t n) {
    if (v > n || !v) {
      return 0;
    }
    int64_t ret = 1, b = 10, v1 = 9;
    while (v * b + v1 <= n) {
      ret += b;
      b *= 10;
      v1 = v1 * 10 + 9;
    }
    if (v * b > n) {
      return ret;
    } else {
      return n - v * b + ret + 1;
    }
  }
public:
  static int findKthNumber(int64_t n, int64_t k) {
    int64_t v = 0, s = 0;
    for (int64_t d = 1; d <= 9; ++d) {
      int64_t s1 = s + smaller(d, n);
      if (s1 >= k) {
        v = d;
        break;
      } else {
        s = s1;
      }
    }
    //std::cout << s << ' ' << v << std::endl;
    while (v * 10 <= n) {
      s += 1;
      if (s == k) {
        return v;
      }
      int64_t v10 = v * 10;
      //std::cout << "v10: " << s << std::endl;
      for (int64_t d = 0; d <= 9; ++d) {
        int64_t s1 = s + smaller(v10 + d, n);
        //std::cout << s1 << ' ' << d << std::endl;
        if (s1 >= k) {
          v = v10 + d;
          break;
        } else {
          if (d != 9) {
            s = s1;
          } else {
            v = v10 + 9;
            break;
          }
        }
      }
    }
    return v;
  }
};

int main() {
  Solution sol;
  std::cout << sol.findKthNumber(10000, 10) << std::endl;
}
