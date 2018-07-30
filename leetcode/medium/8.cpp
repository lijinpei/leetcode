#include <iostream>
#include <string>
#include <cctype>
#include <cstdint>

class Solution {
public:
  int myAtoi(const std::string & str) {
    int s = str.size();
    int i = 0;
    for (i = 0; i < s; ++i) {
      if (!isblank(str[i])) {
        break;
      }
    }
    if (i == s) {
      return 0;
    }
    bool sign;
    if ('-' == str[i]) {
      sign = false;
      ++i;
    } else if ('+' == str[i]) {
      sign = true;
      ++i;
    } else if (isdigit(str[i])) {
      sign = true;
    } else {
      return 0;
    }
    int64_t ret = 0;
    if (sign) {
      for (; i < s && isdigit(str[i]); ++i) {
        ret = ret * 10 + str[i] - '0';
        if (ret >= INT32_MAX) {
          return INT32_MAX;
        }
      }
      return ret;
    } else {
      for (; i < s && isdigit(str[i]); ++i) {
        ret = ret * 10 + str[i] - '0';
        if (ret + INT32_MIN >= 0) {
          return INT32_MIN;
        }
      }
      return -ret;
    }
  }
};

int main() {
  std::string input;
  Solution sol;
  while (true) {
    std::cin >> input;
    std::cout << sol.myAtoi(input) << std::endl;
  }
}
