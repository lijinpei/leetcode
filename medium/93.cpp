#include <string>
#include <utility>
#include <vector>

template <int N> struct calc {
  static void run(const std::string &s, const std::string & s1, int p,
                  std::vector<std::string> &ret) {
    int lv = 0;
    for (int l = 1; l <= 3; ++l) {
      if (l + p > s.size()) {
        break;
      }
      lv = lv * 10 + s[l + p - 1] - '0';
      if (lv > 255) {
        break;
      }
      calc<N - 1>::run(s, s1 + s.substr(p, l) + ".", p + l, ret);
      if (!lv) {
        break;
      }
    }
  }
};
template <> struct calc<1> {
  static void run(const std::string &s, const std::string s1, int p,
                  std::vector<std::string> &ret) {
    if (p < s.size() && p + 3 >= s.size()) {
      int v = std::stoi(s.substr(p));
      if (v <= 255 && (s[p] != '0' || p + 1 == s.size())) {
      ret.push_back(s1 + s.substr(p));
      }
    }
  }
};
class Solution {
public:
  std::vector<std::string> restoreIpAddresses(std::string s) {
    std::vector<std::string> ret;
    calc<4>::run(s, {}, 0, ret);
    return ret;
  }
};

int main() {
  Solution sol;
  auto ret = sol.restoreIpAddresses("010010");
}
