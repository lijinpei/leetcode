#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
  int lengthOfLongestSubstring(const std::string & str) {
    std::vector<int> last_pos(256, -1);
    int l = 0, ans = 0;
    for (int i = 0, s = str.size(); i < s; ++i) {
      int c = str[i];
      int nl = i - last_pos[c];
      /*
      l = std::min(l + 1, nl);
      ans = std::max(ans, l);
      */
      ++l;
      if (nl < l) {
        l = nl;
      } else {
        if (l > ans) {
          ans = l;
        }
      }
      last_pos[c] = i;
    }
    return ans;
  }
};
