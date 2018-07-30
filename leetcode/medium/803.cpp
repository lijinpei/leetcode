#include <iostream>
#include <vector>
#include <numeric>

class Solution {
public:
  std::vector<int> hitBricks(std::vector<std::vector<int>> &grid,
                             std::vector<std::vector<int>> &hits) {
    int n = grid.size();
    if (!n) {
      return {};
    }
    int m = grid[0].size();
    if (!m) {
      return {};
    }
    int s = hits.size();
    if (!s) {
      return {};
    }
    std::vector<std::vector<int>> ids(n, std::vector<int>(m));
    int rn = 0;
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < m; ++y) {
        if (grid[x][y]) {
          ids[x][y] = ++rn;
        }
      }
    }
    if (!rn) {
      return std::vector<int>(s);
    }
    std::vector<std::pair<int, int>> xys(rn + 1);
    for (int x = 0, rn1 = 0; rn1 < rn && x < n; ++x) {
      for (int y = 0; rn1 < rn && y < m; ++y) {
        if (grid[x][y]) {
          xys[++rn1] = {x, y};
        }
      }
    }
    if (xys[1].first) {
      return std::vector<int>(s);
    }
    for (int i = 0; i < s; ++i) {
      int x = hits[i][0];
      int y = hits[i][1];
      grid[x][y] = -grid[x][y];
    }
    /*
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < m; ++y) {
        std::cout << grid[x][y] << ' ';
      }
      std::cout << std::endl;
    }
    */
    std::vector<int> father(rn + 1);
    std::iota(father.begin() + 1, father.end(), 1);
    std::vector<int> count(rn + 1, 1);
    std::vector<int> rank(rn + 1);
    std::vector<int> pc_stack(rn);
    auto path_compress = [&](int id) {
      int tos = 0;
      while (true) {
        int fa = father[id];
        if (fa != id) {
          pc_stack[tos++] = id;
          id = fa;
        } else {
          for (int i = 0; i < tos; ++i) {
            father[pc_stack[i]] = fa;
          }
          return fa;
        }
      }
    };
    // make id2 father of id1
    auto link_to = [&](int id1, int id2) {
      count[id2] += count[id1];
      father[id1] = id2;
    };
    // predicate: (x1, y1) and (x2, y2) are valid
    auto merge = [&](int x1, int y1, int x2, int y2) {
      int id1 = ids[x1][y1], id2 = ids[x2][y2];
      /*
      std::cout << "merge1 " << x1 << ' ' << y1 << ' ' << id1 << std::endl;
      std::cout << "merge2 " << x2 << ' ' << y2 << ' ' << id2 << std::endl;
      */
      int fa1 = path_compress(id1), fa2 = path_compress(id2);
      if (fa1 == fa2) {
        return;
      }
      int &r1 = rank[fa1], r2 = rank[fa2];
      if (r1 < r2) {
        link_to(fa1, fa2);
        /*
        std::cout << "case 1\n";
        std::cout << count[fa2] << std::endl;
        */
      } else if (r1 == r2) {
        ++r1;
        link_to(fa2, fa1);
        /*
        std::cout << "case 2\n";
        std::cout << count[fa1] << std::endl;
        */
      } else {
        link_to(fa2, fa1);
        /*
        std::cout << "case 3\n";
        std::cout << count[fa1] << std::endl;
        */
      }
    };
    // predicate: (x1, y1) is valid
    auto try_merge = [&](int x1, int y1, int x2, int y2) {
      if (x2 < 0 || x2 >= n || y2 < 0 || y2 >= m || grid[x2][y2] <= 0) {
        return;
      }
      merge(x1, y1, x2, y2);
    };
    int y0;
    bool has_y0 = false;
    /*
    for (int x = 0; x < n; ++x) {
      for (int y = 0; y < m; ++y) {
        std::cout << grid[x][y] << ' ';
      }
      std::cout << std::endl;
    }
    */
    {
      for (int y = 0; y < m; ++y) {
        if (grid[0][y] > 0) {
          if (has_y0) {
            merge(0, y0, 0, y);
          } else {
            has_y0 = true;
            y0 = y;
          }
        }
      }
      for (int x = 1; x < n; ++x) {
        bool flag = grid[x][0] > 0;
        if (flag && grid[x - 1][0] > 0) {
          merge(x - 1, 0, x, 0);
        }
        for (int y = 1; y < m; ++y) {
          if (grid[x][y] > 0) {
            if (grid[x - 1][y] > 0) {
              merge(x - 1, y, x, y);
            }
            if (flag) {
              merge(x, y - 1, x, y);
            }
            flag = true;
          } else {
            flag = false;
          }
        }
      }
    }
    auto calc_sum0 = [&]() {
      if (has_y0) {
        int id = ids[0][y0];
        int fa = path_compress(id);
        return count[fa];
      } else {
        return 0;
      }
    };
    int sum0 = calc_sum0();
    std::vector<int> ret(s);
    /*
    std::cout << "start merge\n";
    */
    while (s--) {
      int x = hits[s][0];
      int y = hits[s][1];
      if (!grid[x][y]) {
        continue;
      }
      grid[x][y] = 1;
      if (x == 0) {
        try_merge(0, y, x + 1, y);
        try_merge(0, y, x, y + 1);
        try_merge(0, y, x, y - 1);
        if (has_y0) {
          merge(0, y, 0, y0);
        } else {
          has_y0 = true;
          y0 = y;
        }
      } else {
        try_merge(x, y, x + 1, y);
        try_merge(x, y, x - 1, y);
        try_merge(x, y, x, y + 1);
        try_merge(x, y, x, y - 1);
      }
      int sum1 = calc_sum0();
      ret[s] = (sum1 == sum0 ? 0 : sum1 - sum0 - 1);
      sum0 = sum1;
    }
    return ret;
  }
};

int main() {
  Solution sol;
  std::vector<std::vector<int>> grid{{0,1,1,1,1,1},{1,1,1,1,1,1},{0,0,1,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
  std::vector<std::vector<int>> hits{{1,3},{3,5},{0,3},{3,3},{1,1},{4,2},{1,0},{3,0},{4,5},{2,1},{4,4},{4,0},{2,4},{2,5},{3,4},{0,5},{0,4},{3,2},{1,5},{4,1},{2,2},{0,2}};
  auto ret = sol.hitBricks(grid, hits);
  for (auto v : ret) {
    std::cout << v << ' ';
  }
  std::cout << std::endl;
}
