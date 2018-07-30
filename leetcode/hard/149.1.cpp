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
#include <algorithm>
#include <iostream>

struct Point {
   int x;
   int y;
   Point() : x(0), y(0) {}
   Point(int a, int b) : x(a), y(b) {}
};

class Solution {
public:
    int maxPoints(std::vector<Point>& points) {
      size_t s = points.size();
      if (s <= 2) {
        return s;
      }
      size_t ans = 2;
      size_t same;
      std::vector<int> ar(s);
      std::vector<bool> flag(s, false);
      size_t ar_s;
      int* p_ar = ar.data();

      for (size_t i = 0; i < s; ++i) {
        if (flag[i]) {
          continue;
        }
        int x0 = points[i].x, y0 = points[i].y;
        auto f = [&] (size_t p, size_t q) {
          int64_t x1 = points[p].x - x0, y1 = points[p].y - y0;
          int64_t x2 = points[q].x - x0, y2 = points[q].y - y0;
          if (x1 < 0) {
            x1 = -x1;
            y1 = -y1;
          }
          if (x2 < 0) {
            x1 = -x1;
            y1 = -y1;
          }
          return x1 * y2 - x2 * y1;
        };
        same = 1;
        ar_s = 0;
        // sort all points with respect to their slope to i
        for (size_t j = i + 1; j < s; ++j) {
          if (x0 == points[j].x && y0 == points[j].y) {
            ++same;
            flag[j] = true;
          } else {
            ar[ar_s++] = j;
          }
        }
        if (same > ans) {
          ans = same;
        }

        std::sort(ar.begin(), ar.begin() + ar_s, [&](int i, int j) { return f(i, j) < 0; });
        for (size_t j = 0; j < ar_s;) {
          /*
          size_t p = std::upper_bound(p_ar + j, p_ar + ar_s, ar[j], [&](int i, int j) { return f(i, j) < 0; }) - p_ar;
          */
          size_t p = j + 1;
          for (;p < ar_s; ++p) {
            if (f(ar[p], ar[j]) != 0) {
              break;
            }
          }
          size_t k = p - j + same;
          if (k > ans) {
            ans = k;
          }
          j = p;
        }
      }
      return ans;
    }
};

int main() {
  std::vector<Point> input;
  input.emplace_back(-4, 1);
  input.emplace_back(-7, 7);
  input.emplace_back(-1, 5);
  input.emplace_back(9, -25);
  Solution sol;
  std::cout << sol.maxPoints(input) << std::endl;
}
