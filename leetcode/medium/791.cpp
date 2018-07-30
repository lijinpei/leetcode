#include <string>
#include <array>

class Solution {
public:
  std::string customSortString(const std::string &S, const std::string &T) {
    const int C_NUM = 26;
    std::array<int, C_NUM> count{0};
    for (const auto & c : T) {
      ++count[c - 'a'];
    }
    std::string ret(T.size(), ' ');
    int i = 0;
    for (const auto & ch : S) {
      int c = ch - 'a';
      std::fill(&ret[i], &ret[i + count[c]], ch);
      i += count[c];
      count[c] = 0;
    }
    for (int c = 0; c < C_NUM; ++c) {
      if (count[c]) {
        char ch = c + 'a';
        std::fill(&ret[i], &ret[i + count[c]], ch);
        i += count[c];
      }
    }
    return ret;
  }
};
