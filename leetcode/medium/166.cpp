#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class Solution {
public:
  std::string fractionToDecimal(int64_t numerator, int64_t denominator) {
    if (0 == numerator) {
      return "0";
    }
    bool neg = false;
    if (numerator < 0) {
      neg = true;
      numerator = -numerator;
    }
    if (denominator < 0) {
      neg = !neg;
      denominator = -denominator;
    }
    std::string ret;
    if (neg) {
      ret = "-";
    }
    int64_t n1 = numerator / denominator, n2 = numerator % denominator;
    ret += std::to_string(n1);
    if (!n2) {
      return ret;
    }
    ret += ".";
    //ret.reserve(ret.size() + denominator + 2);
    std::unordered_map<int, int> p;
    while (true) {
      if (p[n2]) {
        ret.insert(p[n2], 1, '(');
        ret.append(1, ')');
        break;
      } else {
        p[n2] = ret.size();
        int64_t v = n2 * 10 / denominator;
        n2 = n2 * 10 % denominator;
        ret += '0' + v;
        if (!n2) {
          break;
        }
      }
    }
    return ret;
  }
};

int main() {
  Solution sol;
  std::cout << sol.fractionToDecimal(1, 2) << std::endl;
  std::cout << sol.fractionToDecimal(2, 1) << std::endl;
  std::cout << sol.fractionToDecimal(2, 3) << std::endl;
  std::cout << sol.fractionToDecimal(-50, 3) << std::endl;
  std::cout << sol.fractionToDecimal(50, -3) << std::endl;
  std::cout << sol.fractionToDecimal(-2147483648, -1999) << std::endl;
  std::cout << sol.fractionToDecimal(1, 333) << std::endl;
  std::cout << sol.fractionToDecimal(1, 214748364) << std::endl;
  std::cout << sol.fractionToDecimal(-1, -2147483648) << std::endl;
}
