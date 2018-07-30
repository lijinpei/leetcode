#include <string>
#include <vector>

class Solution {
public:
  bool isMatch(const std::string &s, const std::string &p) {
    int ss = s.size();
    int ps = p.size();
    std::vector<bool> match(ss + 1);
    match[0] = true;
    for (int i = 0; i < ps; ++i) {
      char c = p[i];
      if (c == '.') {
        if (i + 1 < ps && p[i + 1] == '*') {
          bool b = match[0];
          for (int j = 1; j <= ss; ++j) {
            b = b || match[j];
            match[j] = b;
          }
          ++i;
        } else {
          for (int j = ss; j; --j) {
            match[j] = match[j - 1];
          }
          match[0] = false;
        }
      } else {
        if (i + 1 < ps && p[i + 1] == '*') {
          int ls = ss + 1;
          for (int ls1 = ss; ls1 >= 0; --ls1) {
            char cs = s[ls1 - 1];
            if (cs == c) {
              continue;
            }
            if (ls != ls1 + 1) {
              bool b = match[ls1];
              for (int ls2 = ls1 + 1; ls2 < ls; ++ls2) {
                b = b || match[ls2];
                match[ls2] = b;
              }
            }
            ls = ls1;
          }
          ++i;
        } else {
          for (int j = ss; j; --j) {
            match[j] = match[j - 1] && s[j - 1] == c;
          }
          match[0] = false;
        }
      }
    }
    return match[ss];
  }
};
