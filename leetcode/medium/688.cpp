#include <vector>

class Solution {
public:
  double knightProbability(int N, int K, int r, int c) {
    std::vector<std::vector<double>> p1(N + 4, std::vector<double>(N + 4, 0));
    std::vector<std::vector<double>> p2(N + 4, std::vector<double>(N + 4, 0));
    auto P1 = [&](int x, int y) -> double & { return p1[x + 2][y + 2]; };
    auto P2 = [&](int x, int y) -> double & { return p2[x + 2][y + 2]; };
    for (int x = 0; x < N; ++x) {
      for (int y = 0; y < N; ++y) {
        P1(x, y) = 1;
      }
    }
    while (K--) {
      for (int x = 0; x < N; ++x) {
        for (int y = 0; y < N; ++y) {
          P2(x, y) =
              0.125 * (P1(x + 1, y + 2) + P1(x + 1, y - 2) + P1(x + 2, y + 1) +
                       P1(x + 2, y - 1) + P1(x - 1, y + 2) + P1(x - 1, y - 2) +
                       P1(x - 2, y + 1) + P1(x - 2, y - 1));
        }
      }
      std::swap(p1, p2);
    }
    return P1(r, c);
  }
};
