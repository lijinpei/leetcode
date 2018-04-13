#include <iostream>
#include <vector>

class Solution {
  struct bfs_node {
    int board[6];
    int n, fa, d;
  };
  static int order(int b[6]) {
    static int a[6] = {120, 24, 6, 2, 1, 1};
    auto ret = 0;
    for (int i = 0; i < 6; ++i) {
      int v = b[i], n = 0;
      for (int j = i + 1; j < 6; ++j) {
        if (b[j] < v) {
          ++n;
        }
      }
      ret += n * a[i];
    }
    return ret;
  }
  bfs_node queue[720];
public:
  int slidingPuzzle(std::vector<std::vector<int>> &board) {
    queue[0] = bfs_node{{board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2]}, -1, 4, 0};
    int (&b0)[6] = queue[0].board;
    /*
      for (auto v : b0) {
        std::cout << v << ' ';
      }
      std::cout << std::endl;
      */
    int bt[6] = {1, 2, 3, 4, 5, 0};
    int n0 = order(b0);
    int nt = order(bt);
    if (n0 == nt) {
   //           std::cout << "return 2\n";
      return 0;
    }
    bool visit[720] = {};
    visit[n0] = true;
    int head = 0, tail = 1;
    auto expand = [&](int p1, int d, int i, int p2) {
      queue[p2] = queue[p1];
      queue[p2].fa = d;
      queue[p2].d = queue[p1].d + 1;
      int (& b)[6] = queue[p2].board;
      int nb;
      switch (d) {
        case 0:
          if (i >= 3) {
            return false;
          }
          std::swap(b[i], b[i + 3]);
          break;
        case 1:
          if (i < 3) {
            return false;
          }
          std::swap(b[i], b[i - 3]);
          break;
        case 2:
          if (i == 2 || i == 5) {
            return false;
          }
          std::swap(b[i], b[i + 1]);
          break;
        case 3:
          if (i == 0 || i == 3) {
            return false;
          }
          std::swap(b[i], b[i - 1]);
          break;
        default:
          return false;
      }
      /*
      for (auto v : b) {
        std::cout << v << ' ';
      }
      std::cout << std::endl;
      */
      nb = order(b);
      if (!visit[nb]) {
        queue[p2].n = nb;
        visit[nb] = true;
        return true;
      } else {
        return false;
      }
    };
    while (head < tail) {
      int dual = queue[head].fa ^ 1;
      int j = 0;
      for (; j < 6; ++j) {
        if (!queue[head].board[j]) {
          break;
        }
      }
      for (int i = 0; i < 4; ++i) {
        if (i != dual) {
          if (expand(head, i, j, tail)) {
            if (queue[tail].n == nt) {
       //       std::cout << "return 1\n";
              return queue[tail].d;
            }
            ++tail;
          }
        }
      }
      ++head;
    }
    return -1;
  }
};

int main() {
  std::vector<std::vector<int>> input{{3, 2, 4}, {1, 5, 0}};
  Solution sol;
  std::cout << sol.slidingPuzzle(input) << std::endl;
}
