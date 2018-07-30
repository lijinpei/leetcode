#include <string>
#include <iostream>

class Solution {
  uint64_t diff;
  std::string ans;
  int64_t v0;
  int64_t v1;

  bool isPalindromic(const std::string & n, size_t s1, size_t s) {
    for (size_t i = 0; i < s1; ++i) {
      if (n[i] != n[s - 1 -i]) {
        return false;
      }
    }
    return true;
  }

  std::string Palindromic(const std::string & n, size_t s1, size_t s) {
    std::string m(s, '0');
    for (size_t i = 0; i < s1; ++i) {
      m[i] = m[s - 1 - i] = n[i];
    }
    return m;
  }

  template <bool first = false>
  void updateAns(const std::string &s) {
    if (first) {
      ans = s;
      v1 = std::stoll(s);
      diff = std::abs(v1 - v0);
      return;
    }
    int64_t tmp_v = std::stoll(s);
    uint64_t n_diff = std::abs(tmp_v - v0);
    if (n_diff < diff || (n_diff == diff && tmp_v < v1)) {
      diff = n_diff;
      ans = s;
      v1 = tmp_v;
    }
  }

public:
  std::string nearestPalindromic(std::string n) {
    size_t s = n.size();
    size_t s1 = (s + 1) / 2;
    v0 = std::stoll(n);
    std::string n1(s + 1, '0');
    n1[0] = '1';
    n1[s] = '1';
    updateAns<true>(n1);
    if (s != 1) {
      updateAns(std::string(s - 1, '9'));
    }
    if (!isPalindromic(n, s1, s)) {
      updateAns(Palindromic(n, s1, s));
    }
    int64_t v = std::stoll(n.substr(0, s1));
    n1 = std::to_string(v - 1);
    if (n1.size() == s1) {
      updateAns(Palindromic(n1 + std::string(s - s1, '0'), s1, s));
    }
    n1 = std::to_string(v + 1);
    if (n1.size() == s1) {
      updateAns(Palindromic(n1 + std::string(s - s1, '0'), s1, s));
    }
    return ans;
  }
};

int main() {
  Solution sol;
  /*
  std::cout << sol.nearestPalindromic("123") << std::endl;
  std::cout << sol.nearestPalindromic("121") << std::endl;
  std::cout << sol.nearestPalindromic("10") << std::endl;
  std::cout << sol.nearestPalindromic("11") << std::endl;
  std::cout << sol.nearestPalindromic("12") << std::endl;
  std::cout << sol.nearestPalindromic("88") << std::endl;
  std::cout << sol.nearestPalindromic("100") << std::endl;
  */
  std::cout << sol.nearestPalindromic("1") << std::endl;
  std::cout << sol.nearestPalindromic("1213") << std::endl;
}
