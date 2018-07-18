#include <vector>
#include <utility>

class Solution {
  class BlockItor {
    static constexpr int block[9][2] = {{0, 0}, {0, 1}, {0, 2},
                              {1, 0}, {1, 1}, {1, 2},
                              {2, 0}, {2, 1}, {2, 2}
    };
    const int x, y;
    int state;
  public:
    BlockItor(int x, int y) : x(x), y(y), state(0) {
    }
    std::pair<int, int> operator()() {
      auto ret = std::make_pair(x + block[state][0], y + block[state][1]);
      ++state;
      return ret;
    }
  };
  class RowItor {
    const int x;
    int state;
  public:
    RowItor(int x) : x(x), state(0) {
    }
    std::pair<int, int> operator()() {
      return {x, state++};
    }
  };
  class ColItor {
    const int y;
    int state;
  public:
    ColItor(int y) : y(y), state(0) {
    }
    std::pair<int, int> operator()() {
      return {state++, y};
    }
  };
  class DiagItor {
    const bool reverse;
    int state;
  public:
    DiagItor(bool rev) : reverse(rev), state(0) {
    }
    std::pair<int, int> operator()() {
      auto ret = std::make_pair(state, reverse ? 8 - state : state);
      state++;
      return ret;
    }
  };
  template <class Itor>
    bool check(Itor && itor) {
      ++epoch;
      for (int i = 0; i < 9; ++i) {
        auto ret = itor();
        int v = (*board)[ret.first][ret.second];
        if (v == '.') {
          continue;
        }
        v -= '1';
        if (flag[v] == epoch) {
          return false;
        }
        flag[v] = epoch;
      }
      return true;
    }
  std::vector<std::vector<char>> * board;
  int epoch;
  int flag[9];
public:
  bool isValidSudoku(std::vector<std::vector<char>>& board_) {
    board = &board_;
    std::fill(flag, flag + 9, 0);
    epoch = 0;
    for (int x = 0; x < 9; x += 3) {
      for (int y = 0; y < 9; y += 3) {
        if (!check(BlockItor(x, y))) {
          return false;
        }
      }
    }
    for (int i = 0; i < 9; ++i) {
      if (!check(RowItor(i))) {
        return false;
      }
      if (!check(ColItor(i))) {
        return false;
      }
    }
    return true;
    //return check(DiagItor(true)) && check(DiagItor(false));
  }
};

constexpr int Solution::BlockItor::block[9][2];
int main() {
  Solution sol;
  std::vector<std::vector<char>> input(9, std::vector<char>(9, '.'));
  sol.isValidSudoku(input);
}
