#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
};

int direction(const Point & p1, const Point & p2, const Point & p3) {
  const int x1 = p2.x - p1.x, y1 = p2.y - p1.y;
  const int x2 = p3.x - p1.x, y2 = p3.y - p1.y;
  return x1 * y2 - x2 * y1;
}

class Solution {
public:
  std::vector<Point> outerTrees(std::vector<Point> &points) {
    int n = points.size();
    if (n <= 3) {
      return points;
    }
    auto my_compare = [&](const Point & p1, const Point & p2) {
      int d = direction(points[0], p1, p2);
      if (d != 0) {
        return d > 0 ? true : false;
      }
      if (p1.x != p2.x) {
        return p1.x > p2.x;
      }
      return p1.y > p2.y;
    };
    Point mp = points[0];
    int mpp = 0;
    for (int i = 1; i < n; ++i) {
      if (points[i].x < mp.x || (points[i].x == mp.x && points[i].y < mp.y)) {
        mpp = i;
        mp = points[i];
      }
    }
    std::swap(points[0], points[mpp]);
    std::sort(points.begin() + 1, points.end(), my_compare);
    std::vector<Point> ret;
    ret.resize(n + 1);
    ret[0] = points[0];
    ret[1] = points[1];
    int tos = 1;
    auto reorder_tos = [&]() {
      /*
      std::cout << "reorder\n";
      std::cout << ret[tos].x << ':' << ret[tos].y << std::endl;
      std::cout << ret[tos - 1].x << ':' << ret[tos - 1].y << std::endl;
      std::cout << ret[tos - 2].x << ':' << ret[tos - 2].y << std::endl;
      */
      int x1 = ret[tos].x - ret[tos - 1].x;
      int x2 = ret[tos - 1].x - ret[tos - 2].x;
      if (x1) {
        if (x1 * x2 < 0) {
          std::swap(ret[tos], ret[tos - 1]);
          return;
        }
      }
      int y1 = ret[tos].y - ret[tos - 1].y;
      int y2 = ret[tos - 1].y - ret[tos - 2].y;
      if (y1 * y2 < 0) {
        std::swap(ret[tos], ret[tos - 1]);
        return;
      }
    };
    auto push_stack = [&](const Point & p) {
      /*
      std::cout << "push_back\n";
      std::cout << p.x << ':' << p.y << std::endl;
      */
      int d;
      while (tos >= 1) {
        d = direction(ret[tos - 1], ret[tos], p);
        if (d >= 0) {
          break;
        } else {
          --tos;
        }
      }
      ret[++tos] = p;
      if (d == 0) {
        reorder_tos();
      }
    };
    for (int i = 2; i < n; ++i) {
      push_stack(points[i]);
    }
    //push_stack(points[0]);
    ret.resize(tos + 1);
    return ret;
  }
};

int main() {
  Solution sol;
  //std::vector<Point> input{{1,1},{2,2},{2,0},{2,4},{3,3},{4,2}};
  std::vector<Point> input{{1,2},{2,2},{4,2}};
  auto ret = sol.outerTrees(input);
  for (auto v : ret) {
    std::cout << v.x << ':' << v.y << ' ';
  }
  std::cout << std::endl;
}
