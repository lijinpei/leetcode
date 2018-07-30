#include <string>

class Solution {
public:
  bool isScramble(const std::string &s1, const std::string &s2) {
    if (s1 == s2) {
      return true;
    }
    int count[256] = {};
    for (auto c : s1) {
      ++count[int(c)];
    }
    for (auto c : s2) {
      --count[int(c)];
    }
    for (auto c : count) {
      if (c) {
        return false;
      }
    }
    for (int i = 1, s = s1.size(); i < s; ++i) {
      const std::string &s11 = s1.substr(0, i);
      const std::string &s12 = s1.substr(i, s - i);
      const std::string &s21 = s2.substr(0, i);
      const std::string &s22 = s2.substr(i, s - i);
      const std::string &s31 = s2.substr(0, s - i);
      const std::string &s32 = s2.substr(s - i, i);
      if ((isScramble(s11, s21) && isScramble(s12, s22)) ||
          (isScramble(s11, s32) && isScramble(s12, s31))) {
        return true;
      }
    }
    return false;
  }
};
