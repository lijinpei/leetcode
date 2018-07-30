#include <string>
#include <vector>

class Solution {
  static int M(int v) {
    const int mv = 1000000007;
    return v >= mv ? v - mv : v;
  }
  struct ABCD {
    int v[4];
    int sum() {
      return M(M(v[0] + v[1]) + M(v[2] + v[3]));
    }
  };
public:
  int countPalindromicSubsequences(const std::string &S) {
    int s = S.size();
    std::vector<ABCD> dp0(s), dp1(s), dp2(s);
    for (int i = 0; i < s; ++i) {
      dp1[i].v[S[i] - 'a'] = 1;
    }
    for (int l = 2; l <= s; ++l) {
      for (int i = 0; i + l <= s; ++i) {
        for (int c = 0; c < 4; ++c) {
          char ch = c + 'a';
          bool b1 = S[i] == ch, b2 = S[i + l - 1] == ch;
          if (!b1) {
            dp0[i].v[c] = dp1[i + 1].v[c];
          } else if (!b2) {
            dp0[i].v[c] = dp1[i].v[c];
          } else {
            dp0[i].v[c] = M(2 + dp2[i + 1].sum());
          }
        }
      }
      std::swap(dp0, dp1);
      std::swap(dp0, dp2);
    }
    return dp1[0].sum();
  }
};
