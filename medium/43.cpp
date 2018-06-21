#include <string>

class Solution {
  std::string solve(int s1, const std::string & num1, int s2, const std::string & num2) {
    std::string ret(s1 + s2 + 1, '\0');
    std::string tmp(s1 + 1, '\0');
    auto multiply = [](std::string & tmp, const std::string & num1, int s1, int c) {
      int carry = 0;
      for (int i = s1 - 1; i >= 0; --i) {
        int c1 = num1[i];
        c1 = c1 * c + carry;
        carry = c1 / 10;
        tmp[i + 1] = c1 % 10;
      }
      tmp[0] = carry;
    };
    auto add = [](std::string & ret, int lp, const std::string & tmp, int tmps) {
      int carry = 0;
      for (int i = tmps; i >= 0; --i, --lp) {
        carry += ret[lp] + tmp[i];
        ret[lp] = carry % 10;
        carry /= 10;
      }
      while (carry) {
        carry += ret[lp];
        ret[lp] = carry % 10;
        carry /= 10;
        --lp;
      }
    };
    for (int j = s2 - 1; j >= 0; --j) {
      multiply(tmp, num1, s1, num2[j]);
      add(ret, s1 + j + 1, tmp, s1);
    }
    int p = 0;
    for (int pe = s1 + s2 + 1; p < pe; ++p) {
      if (ret[p]) {
        break;
      }
    }
    int i = 0;
    for (int j = p, je = s1 + s2 + 1; j < je; ++i, ++j) {
      ret[i] = ret[j] + '0';
    }
    ret.resize(i);
    if (!i) {
      ret = "0";
    }
    return ret;
  }
public:
  std::string multiply(std::string num1, std::string num2) {
    int s1 = num1.size();
    int s2 = num2.size();
    for (auto & c : num1) {
      c -= '0';
    }
    for (auto & c : num2) {
      c -= '0';
    }
    return s1 >= s2 ? solve(s1, num1, s2, num2) : solve(s2, num2, s1, num1);
  }
};
