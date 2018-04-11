#include <iostream>
#include <cassert>
#include <algorithm>
#include <string>
#include <vector>

class Solution {
public:
  std::string shortestPalindrome(std::string &str) {
    int s = str.size();
    if (!s) {
      return "";
    }
    std::vector<int> kmp(s);
    int p = kmp[0] = -1;
    for (int i = 1; i < s; ++i) {
      char c = str[i];
      do {
        if (str[p + 1] == c) {
          ++p;
          break;
        } else {
          if (p >= 0) {
            p = kmp[p];
          } else {
            break;
          }
        }
      } while (true);
      kmp[i] = p; 
    }
    /*
    for (auto v : kmp) {
      std::cout << v << ' ';
    }
    std::cout << std::endl;
    */
    int p1 = -1, p2 = s - 1;
    while (true) {
      char c2 = str[p2];
      do {
          if (p1 + 1 == p2) {
            int l = p1 + p1 + 3;
            std::string ret(str, l, s - l);
            std::reverse(ret.begin(), ret.end());
            return ret + str;
          } else if (p1 == p2) {
            int l = p1 + p1 + 1 + 1;
            std::string ret(str, l, s - l);
            std::reverse(ret.begin(), ret.end());
            return ret + str;
          }
        if (str[p1 + 1] == c2) {
          ++p1;
          --p2;
          break;
        } else if (p1 >= 0) {
          p1 = kmp[p1];
        } else {
          --p2;
          break;
        }
      } while (true);
      if (p1 >= s || p2 < 0) {
        break;
      }
    }
    assert(false);
    std::reverse(str.begin(), str.end());
    return str;
  }
};

int main() {
  Solution sol;
  std::string s1("abcd");
  auto ret = sol.shortestPalindrome(s1);
  std::cout << ret << std::endl;
}
