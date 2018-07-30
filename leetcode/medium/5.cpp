#include <cassert>
#include <string>
#include <vector>

class Solution {
public:
  std::string longestPalindrome(const std::string &str) {
    int s = str.size();
    if (s <= 1) {
      return str;
    }
    int ml = 1, mp = 0;
    for (int i = 0; i < s; ++i) {
      int l = std::min(i, s - i - 1);
      int j = 1;
      for (; j <= l; ++j) {
        if (str[i - j] != str[i + j]) {
          break;
        }
      }
      int nl = j + j - 1;
      if (nl > ml) {
        ml = nl;
        mp = i - j + 1;
      }
      if (i + 1 < s && str[i] == str[i + 1]) {
        if (ml < 2) {
          ml = 2;
          mp = i;
        }
        int l = std::min(i, s - i - 2);
        int j = 1;
        for (; j <= l; ++j) {
          if (str[i - j] != str[i + j + 1]) {
            break;
          }
        }
        int nl = j + j;
        if (nl > ml) {
          ml = nl;
          mp = i - j + 1;
        }
      }
    }
    return str.substr(mp, ml);
  }
};

