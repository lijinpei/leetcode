#include <iostream>
#include <algorithm>
#include <string>

/* this implementation is inefficient */

class Solution {
  int ans;
  std::string static eat(const std::string &str, int p) {
    int s = str.size();
    char c = str[p];
    int p1 = p, p2 = p + 1, lp1 = p, lp2 = p, n = 1;
    while (true) {
      while (p1 && str[p1 - 1] == c) {
        --p1;
        ++n;
      }
      while (p2 != s && str[p2] == c) {
        ++p2;
        ++n;
      }
      if (n >= 3) {
        lp1 = p1;
        lp2 = p2;
        if (p1) {
          n = 1;
          c = str[--p1];
        } else if (p2 != s) {
          n = 1;
          c = str[p2++];
        } else {
          break;
        }
      } else {
        break;
      }
    }
    return str.substr(0, lp1) + str.substr(lp2, s - lp2);
  }
  void calc(std::string board, std::string hand) {
    if (board.empty()) {
      ans = std::max<int>(ans, hand.size());
      return;
    }
    if (hand.empty()) {
      return;
    }
    for (int i = 0, s1 = hand.size(); i < s1; ++i) {
      if (i && hand[i] == hand[i - 1]) {
        continue;
      }
      char c = hand[i];
      for (int j = 0, s2 = board.size(); j < s2;) {
        while (j < s2 && board[j] != c) {
          ++j;
        }
        if (j && board[j] == board[j - 1]) {
          continue;
        }
        if (j < s2) {
          calc(eat(board.substr(0, j) + std::string(1, hand[i]) +
                   board.substr(j, s2 - j), j),
               hand.substr(0, i) + hand.substr(i + 1, s1 - i - 1));
        }
        ++j;
        while (j < s2 && board[j] == c) {
          ++j;
        }
      }
    }
  }

public:
  int findMinStep(std::string board, std::string hand) {
    ans = -1;
    int s1 = hand.size();
    std::sort(hand.begin(), hand.end());
    calc(board, hand);
    return ans >= 0 ? s1 - ans : -1;
  }
};

int main() {
  Solution sol;
  std::cout << sol.findMinStep("WRRBBW", "RB") << std::endl;
  std::cout << sol.findMinStep("WWRRBBWW", "WRBRW") << std::endl;
  std::cout << sol.findMinStep("G", "GG") << std::endl;
  std::cout << sol.findMinStep("RBYYBBRRB", "YRBGB") << std::endl;
}
