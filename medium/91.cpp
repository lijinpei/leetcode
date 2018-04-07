#include <string>

class Solution {
public:
  int numDecodings(std::string & s) {
    if (!s.size()) {
      return 0;
    }
    int a = 0, b = 1;
    char last_ch = '0';
    for (auto ch : s) {
      int c = ch == '0' ? 0 : b;
      if (last_ch == '1' || (last_ch == '2' && ch <= '6')) {
        c += a;
      }
      a = b;
      b = c;
      last_ch = ch;
    }
    return b;
  }
};
