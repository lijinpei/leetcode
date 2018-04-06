#include <iostream>
#include <string>

class Solution {
public:
  void reverseWords(std::string &str) {
    int s = str.size();
    auto swap = [&](int p1, int p2, int p3) {
      for (int i = p3, j = p2 - 1; i < p1; ++i, --j) {
        str[i] = str[j];
      }
      for (int i = p1, j = p3 + (p2 - p1) - 1; i < j; ++i, --j) {
        std::swap(str[i], str[j]);
      }
    };
    swap(0, s, 0);
    auto next_non_blank = [&](int i) {
      while (i < s && str[i] == ' ') {
        ++i;
      }
      return i;
    };
    auto next_blank = [&](int i) {
      while (i < s && str[i] != ' ') {
        ++i;
      }
      return i;
    };
    int k = 0, i = next_non_blank(0), j = next_blank(i);
    while (i < s) {
      swap(i, j, k);
      k += (j - i + 1);
      str[k - 1] = ' ';
      i = next_non_blank(j + 1);
      j = next_blank(i + 1);
    }
    str = str.substr(0, k ? k - 1 : 0);
  }
};

int main() {
  std::string input(" ");
  Solution sol;
  sol.reverseWords(input);
  std::cout << input;
}
