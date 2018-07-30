#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

class Solution {
public:
  std::string makeLargestSpecial(const std::string & S) {
    std::vector<std::string> v;
    int n = 0, l = 0, s = S.size();
    if (s == 2) {
      return S;
    }
    for (int r = 0; r + 1 < s; ++r) {
      if (S[r] == '1') {
        ++n;
      } else {
        --n;
      }
      if (!n) {
        v.push_back(makeLargestSpecial(S.substr(l, r - l + 1)));
        l = r + 1;
      }
    }
    if (!l) {
      return "1" + makeLargestSpecial(S.substr(1, s - 2)) + "0";
    } else {
      v.push_back(makeLargestSpecial(S.substr(l, s)));
    }
    std::sort(v.begin(), v.end(), std::greater<std::string>());
    std::string ret;
    ret.reserve(s);
    for (const auto & s : v) {
      ret += s;
    }
    return ret;
  }
};

int main() {
  Solution sol;
  std::cout << sol.makeLargestSpecial("101110110011010000") << std::endl;
}
