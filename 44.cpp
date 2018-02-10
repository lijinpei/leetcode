#include <string>
#include <iostream>

class Solution {
public:
  bool isMatch(std::string s, std::string p) {
    std::string::iterator si = s.begin(), se = s.end();
    std::string::iterator pi = p.begin(), pe = p.end();
    std::string::iterator s_backtrack = se, p_backtrack = pe;
    while (si != se) {
      if (*si == *pi || *pi == '?') {
        ++si;
        ++pi;
        continue;
      }
      if (*pi == '*') {
        s_backtrack = si;
        p_backtrack = pi;
        ++pi;
        continue;
      }
      if (s_backtrack != se) {
        ++s_backtrack;
        si = s_backtrack;
        pi = p_backtrack + 1;
        continue;
      }
      return false;
    }
    if (pi == pe) {
      return true;
    }
    for (; pi < pe; ++pi) {
      if (*pi != '*') {
        return false;
      }
    }
    return true;
  }
};

int main() {
  Solution sol;
  /*
  std::cout << sol.isMatch("aa","a") << std::endl;
  std::cout << sol.isMatch("aa","aa") << std::endl;
  std::cout << sol.isMatch("aaa","aa") << std::endl;
  std::cout << sol.isMatch("aa","*") << std::endl;
  std::cout << sol.isMatch("aa","a*") << std::endl;
  std::cout << sol.isMatch("ab","?*") << std::endl;
  std::cout << sol.isMatch("aab","c*a*b") << std::endl;
  std::cout << sol.isMatch("abefcdgiescdfimde","ab*cd?i*de") << std::endl;
  */
  std::cout << sol.isMatch("aaaa","***a") << std::endl;
}
