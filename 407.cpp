#include <vector>
#include <queue>
#include <iostream>

struct P {
  int x, y;
};

class Solution {
public:
  int trapRainWater(std::vector<std::vector<int>>& heightMap) {
    auto compare = [&](const P & p1, const P & p2) {
      return heightMap[p1.x][p1.y] > heightMap[p2.x][p2.y];
    };
    int x = heightMap.size();
    if (!x) {
      return 0;
    }
    int y = heightMap[0].size();
    int n = x * y;
    std::vector<P> container;
    container.reserve(n);
    std::vector<std::vector<bool>> in_pq(x, std::vector<bool>(y, false));
    std::priority_queue<P, decltype(container), decltype(compare)> pq(
        compare, container);
    for (int i = 0; i < x; ++i) {
      pq.push(P{i, 0});
      pq.push(P{i, y - 1});
      in_pq[i][0] = true;
      in_pq[i][y - 1] = true;
    }
    for (int j = 1; j + 1 < y; ++j) {
      pq.push(P{0, j});
      pq.push(P{x - 1, j});
      in_pq[0][j] = true;
      in_pq[x - 1][j] = true;
    }
    int level = 0, ans = 0;
    while (n--) {
      P p = pq.top();
      pq.pop();
      int h = heightMap[p.x][p.y];
      //std::cout << "h: " << h << std::endl;
      if (h < level) {
        ans += level - h;
      } else {
        level = h;
      }
      auto tryAdd = [&](int nx, int ny) {
        if (nx >= 0 && nx < x && ny >= 0 && ny < y && (!in_pq[nx][ny])) {
          //std::cout << "adding " << nx << ' ' << ny << std::endl;
          pq.push(P{nx, ny});
          in_pq[nx][ny] = true;
        }
      };
      tryAdd(p.x - 1, p.y);
      tryAdd(p.x + 1, p.y);
      tryAdd(p.x, p.y - 1);
      tryAdd(p.x, p.y + 1);
    }
    return ans;
  }
};
