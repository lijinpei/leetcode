#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Solution {
public:
  bool canTransform(std::string const &str1, const std::string &str2) {
    int s1 = str1.size(), s2 = str2.size();
    if (s1 != s2) {
      return false;
    }
    int lp = -1;
    for (int i = 0, j = 0, s = s1; ; ++i, ++j) {
      bool b1, b2;
      char c1, c2;
      while ((b1 = i < s) && (c1 = str1[i]) == 'X') {
        ++i;
      }
      while ((b2 = j < s) && (c2 = str2[j]) == 'X') {
        ++j;
      }
      if ((b1 && !b2) || (b2 && !b1)) {
        return false;
      }
      if (!b1 && !b2) {
        break;
      }
      if (c1 != c2) {
        return false;
      }
      if (c1 == 'L') {
        if (lp >= i || j > i) {
          return false;
        }
      } else {
        if (j < i) {
          return false;
        }
      }
      lp = j;
    }
    return true;
  }
};

int main() {
  Solution sol;
  //std::string s1("XXRXXLXXXX"), s2("XXXXRXXLXX");
  std::string s1("XXRXLXRXXX"), s2("XXRLXXXXXR");
  std::cout << sol.canTransform(s1, s2);
}
