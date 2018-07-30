#include <string>
#include <vector>

class Solution {
  static constexpr int C_NUM = 26;
public:
  std::vector<int> partitionLabels(const std::string & S) {
    int last_pos[C_NUM];
    std::fill(last_pos, last_pos + C_NUM, -1);
    int s = S.size();
    for (int i = 0; i < s; ++i) {
      last_pos[S[i] - 'a'] = i;
    }
    std::vector<int> ret;
    for (int i = 0, j = 0, p = -1; j < s; ++i) {
      p = std::max(last_pos[S[i] - 'a'], p);
      if (i == p) {
        ret.push_back(i - j + 1);
        j = i + 1;
      }
    }
    return ret;
  }
};
