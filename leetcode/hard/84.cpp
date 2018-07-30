#include <vector>
#include <utility>

class Solution {
  static inline void calc(int h, int p, int &ans, int& tos, std::vector<std::pair<int, int>> &height_pos) {
      int np = p;
      while (tos >= 0) {
        int h1 = height_pos[tos].first, p1 = height_pos[tos].second;
        if (h1 >= h) {
          int nv = (p - p1) * h1;
          ans = std::max(nv, ans);
          np = p1;
          --tos;
        } else {
          break;
        }
      }
      height_pos[++tos] = std::make_pair(h, np);
  }

public:
  int largestRectangleArea(const std::vector<int> &heights) {
    int s = heights.size();
    if (!s) {
      return 0;
    }
    std::vector<std::pair<int, int>> height_pos(s);
    int ans = 0, tos = -1;
    for (int i = 0; i < s; ++i) {
      calc(heights[i], i, ans, tos, height_pos);
    }
    calc(0, s, ans, tos, height_pos);
    return ans;
  }
};

