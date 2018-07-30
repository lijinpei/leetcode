#include <utility>
#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>

struct Obj {
  int x, y;
public:
  Obj(int x, int y) : x(x), y(y) {}
  bool operator<(const Obj & rhs) const {
    return x < rhs.x;
  }
};

class Solution {
  int N, K;
  std::vector<Obj> &towers, &ballons;
public:
  Solution(int N, int K, std::vector<Obj> &towers, std::vector<Obj> &ballons)
      : N(N), K(K), towers(towers), ballons(ballons) {}
  int calc() {
    std::sort(towers.begin(), towers.end());
    std::sort(ballons.begin(), ballons.end());
    auto last_x = std::numeric_limits<int>::min();
    std::vector<bool> ok(K);
    int last_p = 0;
    for (int i = 0; i < K; ++i) {
      int x = ballons[i].x;
      while (last_p < N && towers[last_p].x <= x) {
        int x1 = towers[last_p].x + towers[last_p].y;
        if (x1 > last_x) {
          last_x = x1;
        }
        ++last_p;
      }
      x += ballons[i].y;
      if (last_x >= x) {
        ok[i] = true;
      }
    }
    last_x = std::numeric_limits<int>::max();
    last_p = N - 1;
    int ans = 0;
    for (int i = K - 1; i >= 0; --i) {
      int x = ballons[i].x;
      while (last_p >= 0 && towers[last_p].x >= x) {
        int x1 = towers[last_p].x - towers[last_p].y;
        if (x1 < last_x) {
          last_x = x1;
        }
        --last_p;
      }
      x -= ballons[i].y;
      if (last_x <= x) {
        ok[i] = true;
      }
      if (ok[i]) {
        ++ans;
      }
    }
    return ans;
  }
};

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; ++t) {
    int N, K;
    std::cin >> N >> K;
    //std::cout << "N: " << N << " K: " << K << std::endl;
    int64_t p1, p2, a1, b1, c1, m1;
    int64_t h1, h2, a2, b2, c2, m2;
    std::cin >> p1 >> p2 >> a1 >> b1 >> c1 >> m1;
    std::cin >> h1 >> h2 >> a2 >> b2 >> c2 >> m2;
    std::vector<Obj> towers, ballons;
    towers.reserve(K);
    ballons.reserve(K);
    towers.emplace_back(p1, h1);
    towers.emplace_back(p2, h2);
    for (int i = 2; i < N; ++i) {
      int p3 = (a1 * p2 + b1 * p1 + c1) % m1 + 1;
      int h3 = (a2 * h2 + b2 * h1 + c2) % m2 + 1;
      //std::cout << p3 << ' ' << h3 << std::endl;
      towers.emplace_back(p3, h3);
      p1 = p2;
      h1 = h2;
      p2 = p3;
      h2 = h3;
    }
    int64_t x1, x2, a3, b3, c3, m3;
    int64_t y1, y2, a4, b4, c4, m4;
    std::cin >> x1 >> x2 >> a3 >> b3 >> c3 >> m3;
    std::cin >> y1 >> y2 >> a4 >> b4 >> c4 >> m4;
    ballons.emplace_back(x1, y1);
    ballons.emplace_back(x2, y2);
    for (int i = 2; i < K; ++i) {
      int x3 = (a3 * x2 + b3 * x1 + c3) % m3 + 1;
      int y3 = (a4 * y2 + b4 * y1 + c4) % m4 + 1;
      //std::cout << x3 << ' ' << y3 << std::endl;
      ballons.emplace_back(x3, y3);
      x1 = x2;
      y1 = y2;
      x2 = x3;
      y2 = y3;
    }
    Solution sol(N, K, towers, ballons);
    std::cout << "Case #" << (t + 1) << ": " << sol.calc() << std::endl;
  }
}
