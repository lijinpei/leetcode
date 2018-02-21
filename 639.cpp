#include <string>

class Solution {
public:
  int numDecodings(const std::string & str) {
    const int32_t v1097 = 1000000007;
    int32_t a = 1, b, c;
    if (isStar(s[0])) {
      b = 9;
    } else {
      b = 1;
    }
    auto minusMod(int32_t & v) {
      if (v >= v1097) {
        v -= v1097;
      };
    };
    auto minusMod(int32_t & v) {
      if (v >= v1097) {
        v %= v1097;
      };
    };
    for (size_t s = 1, s1 = str.size(); s < s1; ++s) {
      switch(str[s]) {
      case '*':
        switch(str[s - 1]) {
          case '*':
            c = a * 26;
            divideMod(c);
        };
        break;
      case '0':
        switch(str[s - 1]) {
        case '*':
          c = a + a;
          minusMod(c);
        case '1':
        case '2':
          c = a;
          break;
        default:
          c = 0;
        };
        break;
      default:
      }
    }
  }
};
