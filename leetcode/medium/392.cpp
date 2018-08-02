#include <string>

class Solution {
public:
  bool isSubsequence(const std::string & s, const std::string & t) {
    int sn = s.size();
    if (!sn) {
      return true;
    }
    int tn = t.size();
    if (tn < sn) {
      return false;
    }
    int ps = 0, pt = 0;
    while (ps < sn && pt < tn) {
      if (s[ps] == t[pt++]) {
        ++ps;
      }
    }
    return ps == sn;
  }
};
