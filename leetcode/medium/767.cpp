#include <string>

class Solution {
public:
  std::string reorganizeString(const std::string &str) {
    int s = str.size();
    if (!s) {
      return "";
    }
    int count[26] = {};
    for (auto c : str) {
      ++count[c - 'a'];
    }
    int mv = count[0], mp = 0;
    for (int p = 1; p < 26; ++p) {
      int nv = count[p];
      if (nv > mv) {
        mv = nv;
        mp = p;
      }
    }
    if (mv > (s + 1) / 2) {
      return "";
    }
    std::string ret(s, 'a' + mp);
    auto pos = [&](int p) {
      return p < s ? p : 1;
    };
    int p = pos(count[mp] * 2 + 1);
    count[mp] = 0;
    for (int i = 0; i < 26; ++i) {
      if (count[i]) {
        char c = 'a' + i;
        for (int j = 0; j < count[i]; ++j) {
          ret[p] = c;
          p = pos(p + 2);
        }
      }
    }
    return ret;
  }
};
