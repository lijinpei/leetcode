/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
#include <vector>
#include <cstdint>

struct Point {
   int x;
   int y;
   Point() : x(0), y(0) {}
   Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
    int maxPoints(std::vector<Point>& points) {
      size_t ans = 2;
      size_t s = points.size();
      if (s <= 2) {
        return s;
      }
      size_t same;
      for (size_t i = 0; i < s; ++i) {
        same = 1;
        for (size_t j = i + 1; j < s; ++j) {
          if (points[i].x == points[j].x && points[i].y == points[j].y) {
            ++same;
            continue;
          }
          size_t v =  0;
          int64_t x0 = points[i].x, y0 = points[i].y;
          int64_t dx = x0 - points[j].x;
          int64_t dy = y0 - points[j].y;
          auto test = [&](size_t k){
            if ((points[k].x - x0) * dy == (points[k].y - y0) * dx) {
              ++v;
            }
          };
          for (size_t k = 0; k < i; ++k) {
            test(k);
          }
          for (size_t k = i + 1; k < j; ++k) {
            test(k);
          }
          for (size_t k = j + 1; k < s; ++k) {
            test(k);
          }
          v += 2;
          if (v > ans) {
            ans = v;
          }
        }
        if (same > ans) {
          ans = same;
        }
      }
      return ans;
    }
};
