#include <iostream>
#include <vector>
#include <algorithm>

struct Pos {
  int x, y, h;
  Pos() {};
  Pos(int x, int y, int h) : x(x), y(y), h(h) {}
};

class pos_compare {
public:
  bool operator()(const Pos & p1, const Pos & p2) {
    return p1.h < p2.h;
  }
};

class Solution {
public:
  int cutOffTree(std::vector<std::vector<int>>& forest) {
    int n = forest.size();
    int m = n ? forest[0].size() : 0;
    if (!m) {
      return 0;
    }
    int t = 0;
    for (auto & r : forest) {
      for (auto v : r) {
        if (v > 1) {
          ++t;
        }
      }
    }
    if (!t) {
      return 0;
    }
    std::vector<Pos> trees(t);
    trees.clear();
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < m; ++y) {
        int h = forest[x][y];
        if (h > 1) {
          trees.emplace_back(x, y, h);
        }
      }
    }
    std::sort(trees.begin(), trees.end(), pos_compare());
    std::vector<std::vector<int>> flag(n, std::vector<int>(m));
    std::vector<std::vector<int>> dist(n, std::vector<int>(m));
    std::vector<std::pair<int, int>> queue(n * m);
    int head, tail;
    auto distance = [&](int x0, int y0, int xt, int yt, int mark) {
      if (x0 == xt && y0 == yt) {
        return 0;
      }
      dist[x0][y0] = 0;
      head = 0;
      tail = 1;
      flag[x0][y0] = mark;
      queue[0] = {x0, y0};
      auto visit = [&](int x, int y, int d) {
        if (x < 0 || x >= n || y < 0 || y >= m) {
          return false;
        }
        if (x == xt && y == yt) {
          return true;
        }
        if (flag[x][y] == mark) {
          return false;
        }
        flag[x][y] = mark;
        if (forest[x][y]) {
          dist[x][y] = d;
          queue[tail++] = {x, y};
        }
        return false;
      };
      while (head < tail) {
        int x = queue[head].first;
        int y = queue[head].second;
        ++head;
        int d = dist[x][y] + 1;
        if (visit(x + 1, y, d) || visit(x - 1, y, d) || visit(x, y + 1, d) ||
            visit(x, y - 1, d)) {
          return d;
        }
      }
      return -1;
    };
    int ans = 0, x = 0, y = 0;
    for (int i = 0; i < t; ++i) {
      int nx = trees[i].x;
      int ny = trees[i].y;
      int d = distance(x, y, nx, ny, i + 1);
      if (d < 0) {
        return -1;
      }
      ans += d;
      x = nx;
      y = ny;
    }
    return ans;
  }
};

int main() {
  Solution sol;
  std::vector<std::vector<int>> input{{54581641,64080174,24346381,69107959},{86374198,61363882,68783324,79706116},{668150,92178815,89819108,94701471},{83920491,22724204,46281641,47531096},{89078499,18904913,25462145,60813308}};
  auto ret = sol.cutOffTree(input);
  std::cout << ret << std::endl;
}
