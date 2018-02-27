#include <string>
#include <iostream>

class Solution {
public:
  int numDecodings(const std::string & str) {
    const int32_t v1097 = 1000000007;
    auto decode1 = [&](int p, int v) -> int {
      char c = str[p];
      if (c == '0') {
        return 0;
      }
      return c == '*' ? v * 9l % v1097 : v;
    };
    auto decode2 = [&](int p, int v) -> int {
      char c1 = str[p - 1], c2 = str[p];
      if (c1 == '*') {
        if (c2 == '*') {
          return 15l * v % v1097;
        } else if (c2 <= '6') {
          return 2 * v % v1097;
        } else {
          return v;
        }
      } else if (c1 == '0') {
        return 0;
      } else if (c1 == '1') {
        return c2 == '*' ? 9l * v % v1097 : v;
      } else if (c1 == '2') {
        if (c2 == '*') {
          return 6l * v % v1097;
        }
        return c2 <= '6' ? v : 0;
      } else {
        return 0;
      }
    };
    int s = str.size();
    if (!s) {
      return 0;
    }
    int a = 1, b, c;
    b = decode1(0, a);
    auto f = [&](int & a, int & b, int & c, int i) {
      c = decode1(i, b) + decode2(i, a);
      if (c >= v1097) {
        c -= v1097;
      }
      //std::cout << c << std::endl;
    };
    int i = 1;
    for (; i + 3 < s; i += 3) {
      f(a, b, c, i);
      f(b, c, a, i + 1);
      f(c, a, b, i + 2);
    }
    for (; i < s; ++i) {
      f(a, b, c, i);
      a = b;
      b = c;
    }
    return b;
  }
};
