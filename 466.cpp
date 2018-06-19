#include <iostream>
#include <string>
#include <vector>

class Solution {
  struct Node {
    int repitition, position;
    Node() : repitition(0), position(0) {}
    Node(int r, int p) : repitition(r), position(p) {}
  };
public:
  int getMaxRepetitions(const std::string & str1, int n1, const std::string & str2, int n2) {
    int s1 = str1.size(), s2 = str2.size();
    if (!s1 || !s2) {
      return 0;
    }
    std::vector<std::vector<Node>> dp(s1, std::vector<Node>(s2));
    {
      char c = str1[s1 - 1];
      if (c == str2[s2 - 1]) {
        dp[s1 - 1][s2 - 1] = Node(1, 0);
      } else {
        dp[s1 - 1][s2 - 1] = Node(0, s2 - 1);
      }
      for (int j = s2 - 2; j >= 0; --j) {
        dp[s1 - 1][j] = Node(0, c == str2[j] ? j + 1 : j);
      }
    }
    for (int i = s1 - 2; i >= 0; --i) {
      char c = str1[i];
      if (str2[s2 - 1] == c) {
        dp[i][s2 - 1] = dp[i + 1][0];
        ++dp[i][s2 - 1].repitition;
      } else {
        dp[i][s2 - 1] = dp[i + 1][s2 - 1];
      }
      for (int j = s2 - 2; j >= 0; --j) {
        dp[i][j] = dp[i + 1][c == str2[j] ? j + 1 : j];
      }
    }
    /*
    for (const auto & row : dp) {
      for (const auto & v : row) {
        std::cout << "{" << v.repitition << ',' << v.position << "} ";
      }
      std::cout << std::endl;
    }
    */
    std::vector<int> dp1(s2, -1);
    std::vector<int> dp2(n1 + 1);
    int i, j = 0, count = 0;
    for (i = 1; i <= n1; ++i) {
      count += dp[0][j].repitition;
      dp2[i] = count;
      if (dp1[j] > 0) {
        break;
      } else {
        dp1[j] = i;
      }
      j = dp[0][j].position;
    }
    if (i > n1) {
      return count / n2;
    } else {
      int i1 = dp1[j];
      int v1 = (n1 - i1 + 1) / (i - i1);
      int v2 = (n1 - i1 + 1) % (i - i1) + i1 - 1;
      /*
      std::cout << v1 << ' ' << v2 << std::endl;
      std::cout << count << ' ' << dp2[i1] << std::endl;
      */
      int n = v1 * (count - dp2[i1]) + dp2[v2];
      /*
      std::cout << n << std::endl;
      */
      return n / n2;
    }
    return 0;
  }
};

int main() {
  Solution sol;
  auto ret = sol.getMaxRepetitions("abc", 4, "ab", 2);
  //auto ret = sol.getMaxRepetitions("abacb", 6, "bcaa", 1);
  std::cout << ret << std::endl;
}
