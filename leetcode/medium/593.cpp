#include <vector>

class Solution {
  struct P {
    int x, y;
    P(std::vector<int> &v) : x(v[0]), y(v[1]) {}
  };
  static bool mean(const P p1, const P p2, const P p3, const P p4) {
    return p1.x + p3.x == p2.x + p4.x && p1.y + p3.y == p2.y + p4.y;
  }
  static bool vert(const P p1, const P p2, const P p3) {
    const int x1 = p1.x - p2.x;
    const int y1 = p1.y - p2.y;
    const int x2 = p3.x - p2.x;
    const int y2 = p3.y - p2.y;
    return x1 * x2 + y1 * y2 == 0;
  }
  static int dist2(const P p1, const P p2) {
    const int dx = p1.x - p2.x;
    const int dy = p1.y - p2.y;
    return dx * dx + dy * dy;
  }
  static bool square(const P p1, const P p2, const P p3, const P p4) {
    int d1 = dist2(p1, p2);
    int d2 = dist2(p2, p3);
    if (!d1) {
      return false;
    }
    if (d1 == d2) {
      return vert(p1, p2, p3) && mean(p1, p2, p3, p4);
    }
    if (d1 * 2 == d2) {
      return vert(p3, p1, p2) && mean(p1, p2, p4, p3);
    }
    return false;
  }

public:
  bool validSquare(std::vector<int> &p1_, std::vector<int> &p2_,
                   std::vector<int> &p3_, std::vector<int> &p4_) {
    const P p1(p1_), p2(p2_), p3(p3_), p4(p4_);
    return square(p1, p2, p3, p4) || square(p1, p3, p2, p4);
  }
};
