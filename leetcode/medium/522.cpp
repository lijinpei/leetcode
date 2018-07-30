#include <vector>
#include <algorithm>
#include <string>

class Solution {
  static bool isSubstr(const std::string & str1, const std::string & str2) {
    int s1 = str1.size(), s2 = str2.size();
    int p1 = 0, p2 = 0;
    for (; p1 < s1; ++p1) {
      char c = str1[p1];
      for (; p2 < s2; ++p2) {
        if (str2[p2] == c) {
          break;
        }
      }
      if (p2 == s2) {
        return false;
      }
      ++p2;
    }
    return true;
  }
public:
  int findLUSlength(std::vector<std::string>& strs) {
    int ans = -1;
    int s = strs.size();
    for (int i = 0; i < s; ++i) {
      bool b = true;
      for (int j = 0; j < s; ++j) {
        if (j != i) {
          if (isSubstr(strs[i], strs[j])) {
            b = false;
            break;
          }
        }
      }
      if (b) {
        ans = std::max<int>(ans, strs[i].size());
      }
    }
    return ans;
  }
};
