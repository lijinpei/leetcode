#include <iostream>
#include <string>

class Solution {
public:
  bool checkValidString(const std::string & s) {
    int m1 = 0, m2 = 0;
    for (const auto c : s) {
      if (c == '(') {
        ++m1;
        ++m2;
      } else if (c == ')') {
        if (m1) {
          --m1;
        }
        --m2;
        if (m2 < 0) {
          return false;
        }
      } else {
        if (m1) {
          --m1;
        }
        ++m2;
      }
    }
    return m1 <= 0 && m2 >= 0;
  }
};

int main() {
  Solution sol;
  sol.checkValidString("(())((())()()(*)(*()(())())())()()((()())((()))(*");
}
