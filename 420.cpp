#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

class Solution {
  std::vector<int> v;
  template <int T = 1>
  void countDown(int & v1, int & v2) {
    if (!v1 || !v2) {
      return;
    }
    int v = std::min(v1, v2 / T);
    v1 -= v;
    v2 -= v * T;
  }
public:
  int strongPasswordChecker(const std::string & str) {
    int needLower = 1, needUpper = 1, needDigit = 1;
    size_t s = str.size();
    auto updateNeed = [&](char c) {
      if (c >= '0' && c <= '9') {
        needDigit = 0;
      } else if (c >= 'a' && c <= 'z') {
        needLower = 0;
      } else if (c >= 'A' && c <= 'Z') {
        needUpper = 0;
      }
    };
    if (s) {
      v.resize(s);
      char l_c = str[0];
      int l_n = 1;
      v[0] = 0;
      updateNeed(l_c);
      for (size_t i = 1; i < s; ++i) {
        char n_c = str[i];
        if (str[i] != l_c) {
          v[i - 1] = l_n;
          l_n = 1;
          l_c = n_c;
        } else {
          ++l_n;
          v[i] = 0;
        }
        updateNeed(n_c);
      }
    v[s - 1] = l_n;
    }
    int needFix = needLower + needUpper + needDigit;
    int ret;
    if (s < 6) {
      ret = std::max<int>(needFix, 6 - s);
    } else {
      int needDelete = std::max<int>(0, s - 20);
      int m3 = 0, m2 = 0, m1 = 0;
      for (int i = 0; i < s; ++i) {
        int vv = v[i];
        if (vv <= 2) {
          continue;
        }
        m3 += (vv - 2) / 3;
        int v1 = (vv - 2) % 3;
        if (v1 == 1) {
          ++m1;
        } else if (v1 == 2) {
          ++m2;
        }
      }
      /*
      std::cout << "needDelete: " << needDelete << std::endl;
      std::cout << "needFix: " << needFix << std::endl;
      std::cout << "m1 m2 m3 " << m1 << ' ' << m2 << ' ' << m3 << std::endl;
      */
      ret = needDelete + needFix;
      countDown(m3, needFix);
      countDown(m2, needFix);
      countDown(m1, needFix);
      countDown(m1, needDelete);
      countDown<2>(m2, needDelete);
      countDown<3>(m3, needDelete);
      ret += m1 + m2 + m3;
    }
    return ret;

  }
};

int main() {
  Solution sol;
  std::cout << sol.strongPasswordChecker("") << std::endl;
  std::cout << sol.strongPasswordChecker("ABABABABABABABABABAB1") << std::endl;
  std::cout << sol.strongPasswordChecker("aaaaaaaaaaaaaaaaaaaaa") << std::endl;
  std::cout << sol.strongPasswordChecker("1010101010aaaB10101010") << std::endl;
  std::cout << sol.strongPasswordChecker("1Abababcaaaabababababa") << std::endl;
  std::cout << sol.strongPasswordChecker("aaAA11") << std::endl;
}
