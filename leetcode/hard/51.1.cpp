#include <string>
#include <vector>

class SolutionImpl {
  int N;
  std::vector<int> pos;
  std::vector<std::string> empty_board;
  std::vector<std::vector<std::string>> ret;
  void addSolution() {
    {
    ret.push_back(empty_board);
    auto & b = ret.back();
    for (int i = 0; i < N; ++i) {
      b[i][pos[i]] = 'Q';
    }
    }
    if ((N & 1) && pos[0] + pos[0] + 1== N) {
      return;
    }
    {
    ret.push_back(empty_board);
    auto & b = ret.back();
    for (int i = 0; i < N; ++i) {
      b[i][N - 1 - pos[i]] = 'Q';
    }
    }
  }
  void search(int n, uint64_t mark, uint64_t left_mark, uint64_t right_mark) {
    if (n == N) {
      return addSolution();
    }
    uint64_t lm = uint64_t(1) << n, rm = uint64_t(1) << (n + N - 1), mm = uint64_t(1);
    for (int i = 0; i < N; ++i) {
      if (!(mark & mm) && !(left_mark & lm) && !(right_mark & rm)) {
        pos[n] = i;
        search(n + 1, mark | mm, left_mark | lm, right_mark | rm);
      }
      lm <<= 1;
      rm >>= 1;
      mm <<= 1;
    }
  }
public:
  SolutionImpl(int n) : N(n), pos(N), empty_board(N, std::string(N, '.')) {}
  std::vector<std::vector<std::string>> solve() {
    for (int i = 0, i1 = (N + 1) / 2; i < i1; ++i) {
      pos[0] = i;
      search(uint64_t(1), (uint64_t(1) << i), (uint64_t(1) << i), (uint64_t(1) << (N - 1 - i)));
    }
    return std::move(ret);
  }
};

class Solution {
public:
  std::vector<std::vector<std::string>> solveNQueens(int n) {
    return SolutionImpl(n).solve();
  }
};
