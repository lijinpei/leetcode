#include <cctype>
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>

class Solution {
public:
  int calculate(const std::string &str) {
    int p = 0, s = str.size();
    auto skip_blank = [&]() {
      while (str[p] == ' ') {
        ++p;
      }
    };
    auto get_num = [&]() {
      int num = 0;
      while (std::isdigit(str[p])) {
        num = num * 10 + str[p++] - '0';
      }
      return num;
    };
    auto get_op = [&]() {
      return str[p++];
    };
    auto calc1 = [](int v1, int v2, char c) {
      return c == '+' ? v1 + v2 : v1 - v2;
    };
    auto calc2 = [](int v1, int v2, char c) {
      return c == '*' ? v1 * v2 : v1 / v2;
    };
    skip_blank();
    int v1 = get_num();
    skip_blank();
    if (p == s) {
      return v1;
    }
    char op1 = get_op();
    while (op1 != '+' && op1 != '-') {
      skip_blank();
      int v2 = get_num();
      v1 = calc2(v1, v2, op1);
      skip_blank();
      if (p == s) {
        return v1;
      }
      op1 = get_op();
    }
    while (true) {
      skip_blank();
      int v2 = get_num();
      skip_blank();
      if (p == s) {
        return calc1(v1, v2, op1);
      }
      char op2 = get_op();
      while (op2 == '*' || op2 == '/') {
        skip_blank();
        int v3 = get_num();
        v2 = calc2(v2, v3, op2);
        skip_blank();
        if (p == s) {
          return calc1(v1, v2, op1);
        }
        op2 = get_op();
      }
      v1 = calc1(v1, v2, op1);
      op1 = op2;
    }
    abort();
  }
};

int main() {
  Solution sol;
  std::cout << sol.calculate(" 3+5 / 2 ") << std::endl;
  std::cout << sol.calculate("1-1+1") << std::endl;
  std::cout << sol.calculate("3/2") << std::endl;
}
