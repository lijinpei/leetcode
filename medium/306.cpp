#include <string>
#include <iostream>

class Solution {
public:
  bool isAdditiveNumber(const std::string & num) {
    auto add = [](const std::string &num1, const std::string &num2)->std::string {
      int s1 = num1.size();
      int s2 = num2.size();
      int s3 = std::max(s1, s2) + 1;
      std::string num3(s3, '0');
      int carry = 0;
      auto safe = [](const std::string &num, int p) -> int {
        if (p >= 0) {
          return num[p] - '0';
        } else {
          return 0;
        }
      };
      for (int i = s3 - 1; i >= 0; --i) {
        carry += safe(num1, s1 - (s3 - i)) + safe(num2, s2 - (s3 - i));
        int v = carry % 10;
        carry /= 10;
        num3[i] = v + '0';
      }
      return num3;
    };
    auto valid = [](const std::string & str) -> bool {
      return str.size() == 1 || str[0] != '0';
    };
    int s = num.size();
    if (!s) {
      return false;
    }
    for (int i = 1; i + 2 <= s; ++i) {
      if (!valid(num.substr(0, i))) {
        continue;
      }
      for (int j = 1; j + i + 1 <= s; ++j) {
        if (!valid(num.substr(i, j))) {
          continue;
        }
        std::string s1 = num.substr(0, i);
        std::string s2 = num.substr(i, j);
        int k = i + j;
        while (true) {
          auto s3 = add(s1, s2);
          if (s3[0] == '0') {
            s3 = s3.substr(1);
          }
          int k1 = k + s3.size();
          if (k1 <= s) {
            if (num.substr(k, s3.size()) != s3) {
              break;
            }
            if (k1 == s) {
              return true;
            }
            k = k1;
            s1 = s2;
            s2 = s3;
          } else {
            break;
          }
        }
      }
    }
    return false;
  }
};
