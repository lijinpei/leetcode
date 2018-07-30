#include <vector>
#include <utility>
#include <iostream>

class Solution {
public:
  int maximalRectangle(std::vector<std::vector<char>>& matrix) {
    int n = matrix.size();
    if (!n) {
      return 0;
    }
    int m = matrix[0].size();
    std::vector<int> max_len(m, 0);
    std::vector<std::pair<int, int>> len_pos(m, {0, 0});
    int tos = -1, ans = 0;
    auto calc = [&](int np, int nl) {
      int np1 = np;
      while (tos >= 0 && len_pos[tos].first >= nl) {
        np1 = len_pos[tos].second;
        int nv = len_pos[tos].first * (np - np1);
        ans = std::max(ans, nv);
        --tos;
      }
      len_pos[++tos] = std::make_pair(nl, np1);
    };
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if ('1' == matrix[i][j]) {
          ++max_len[j];
        } else {
          max_len[j] = 0;
        }
        calc(j, max_len[j]);
      }
      calc(m, 0);
      tos = -1;
    }
    return ans;
  }
};

int main() {
  std::vector<char> v1{'1','0','1','0','0'};
  std::vector<char> v2{'1','0','1','1','1'};
  std::vector<char> v3{'1','1','1','1','1'};
  std::vector<char> v4{'1','0','0','1','0'};
  std::vector<std::vector<char>> input;
  input.push_back(v1);
  input.push_back(v2);
  input.push_back(v3);
  input.push_back(v4);
  Solution sol;
  auto ret = sol.maximalRectangle(input);
  std::cout << ret << std::endl;
}
