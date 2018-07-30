#include <string>
#include <utility>

class Solution {
  struct Exp {
    int coeff;
    int coeff_x;
  };
  // parse till first '\0' or '='
  static std::pair<int, Exp> parse(const std::string & equation, int start = 0) {
    int coeff = 0, coeff_x = 0;
    char c = equation[start];
    while (c) {
      if (c == '=') {
        break;
      }
      bool neg = false;
      if (c == '-') {
        neg = true;
       c = equation[++start];
      }
      if (c == '+') {
       c = equation[++start];
      }
      if (c == 'x') {
       c = equation[++start];
        if (neg) {
          --coeff_x;
        } else {
          ++coeff_x;
        }
        continue;
      }
      int v = c - '0';
      while (true) {
       c = equation[++start];
       if (c >= '0' && c <= '9') {
         v = v * 10 + c - '0';
       } else {
         break;
       }
      }
      if (c == 'x') {
        c = equation[++start];
        if (neg) {
          coeff_x -= v;
        } else {
          coeff_x += v;
        }
      } else {
        if (neg) {
          coeff -= v;
        } else {
          coeff += v;
        }
      }
    }
    return {start, {coeff, coeff_x}};
  }
  static std::string solve(Exp lhs, const Exp & rhs) {
    lhs.coeff -= rhs.coeff;
    lhs.coeff_x -= rhs.coeff_x;
    if (lhs.coeff_x) {
      return std::string("x=") + std::to_string(-lhs.coeff / lhs.coeff_x);
    } else {
      return lhs.coeff ? "No solution" : "Infinite solutions";
    }
  }
public:
  std::string solveEquation(const std::string & equation) {
    auto r1 = parse(equation);
    auto r2 = parse(equation, r1.first + 1);
    return solve(r1.second, r2.second);
  }
};
