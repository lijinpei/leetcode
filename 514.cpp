#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Solution {
public:
  int findRotateSteps(std::string ring, std::string key) {
    auto MIN = [](int v1, int v2) {
      if (v1 < 0) {
        return v2;
      }
      if (v2 < 0) {
        return v1;
      }
      return std::min(v1, v2);
    };
    int rl = ring.size(), rl2 = rl + rl;
    for (auto & c : ring) {
      c -= 'a';
    }
    for (auto & c : key) {
      c -= 'a';
    }
    std::vector<int> pos(26, -1);
    std::vector<std::vector<int>> left(rl2, pos);
    for (int i = 0; i < rl; ++i) {
      pos[ring[i]] = i;
      left[i] = pos;
    }
    for (int i = 0; i < rl; ++i) {
      pos[ring[i]] = i;
      left[i + rl] = pos;
    }
    for (int i = 0; i < rl; ++i) {
      for (int j = 0; j < 26; ++j) {
        if (left[i][j] == -1) {
          left[i][j] = left[i + rl][j];
      }
      }
    }
    std::fill(pos.begin(), pos.end(), rl2);
    std::vector<std::vector<int>> right(rl2, pos);
    for (int i = rl - 1; i >= 0; --i) {
      pos[ring[i]] = i;
    }
    for (int i = rl - 1; i >= 0; --i) {
      pos[ring[i]] = i;
      right[i] = pos;
    }
    for (int i = 0; i < rl; ++i) {
      for (int j = 0; j < 26; ++j) {
        if (right[i][j] >= rl) {
          right[i][j] -= rl;
        }
      }
    }
    std::vector<int> dp1(rl, -1), dp2(rl, -1);
    dp1[0] = 0;
    for (auto c : key) {
      //std::cout << char('a' + c) << std::endl;
      assert(c >= 0 && c < 26);
      for (int i = 0; i < rl; ++i) {
        if (dp1[i] < 0) {
          continue;
        }
        //std::cout << i << ' ' << dp1[i] << std::endl;
        int l = left[i][c];
        if (l != -1) {
          dp2[l] = MIN(dp2[l], (l <= i ? i - l : i + rl - l) + 1 + dp1[i]);
        }
        int r = right[i][c];
        if (r != -1) {
          dp2[r] = MIN(dp2[r], (r >= i ? r - i : r + rl - i) + 1 + dp1[i]);
        }
      }
      std::swap(dp1, dp2);
      std::fill(dp2.begin(), dp2.end(), -1);
    }
    int ans = -1;
    for (auto v : dp1) {
      ans = MIN(ans, v);
    }
    return ans;
  }
};

int main() {
  Solution sol;
  std::cout << sol.findRotateSteps("abc", "aaccbb") << std::endl;
}
