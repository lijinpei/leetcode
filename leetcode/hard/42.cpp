#include <iostream>
#include <vector>
#include <utility>

class Solution {
public:
  int trap(std::vector<int> &height) {
    int s = height.size();
    if (!s) {
      return 0;
    }
    std::vector<int> pos(s);
    pos[0] = 0;
    int ans = 0, tos = 0;
    auto calc = [&](const int p) {
      const int h = height[p];
      int tmp = 0;
      while (tos >= 0) {
        int p1 = pos[tos], h1 = height[p1];
        if (h1 > h) {
          break;
        }
        if (tos) {
          tmp += h1 * (p1 - pos[tos - 1]);
        }
        --tos;
      }
      if (tos < 0) {
        int p1 = pos[0], h1 = height[p1];
        ans += (p - p1 - 1) * h1 - tmp;
      } else {
        int p1 = pos[tos], h1 = height[p];
        ans += (p - p1 - 1) * h1 - tmp;
      }
      pos[++tos] = p;
    };
    for (int i = 1; i < s; ++i) {
      calc(i);
    }
    return ans;
  }
};

int main() {
  Solution sol;
  std::vector<int> input{1};
  auto ret = sol.trap(input);
  std::cout << ret << std::endl;
}
