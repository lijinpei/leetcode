#include <algorithm>

class Solution {
public:
  int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    return int64_t(C - A) * int64_t(D - B) + int64_t(G - E) * int64_t(H - F) -
           std::max<int64_t>(0, int64_t(std::min(C, G)) - std::max(A, E)) *
               std::max<int64_t>(0, int64_t(std::min(D, H)) - std::max(B, F));
  }
};
