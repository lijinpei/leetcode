#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <utility>

class Solution {
public:
  std::string removeKdigits(std::string num, int k) {
    int s = num.size();
    if (s <= k) {
      return "0";
    }
    int l = 0, i = 0;
    for (; k && i < s; ++i) {
      char c = num[i];
      while (k && l && num[l - 1] > c) {
        --k;
        --l;
      }
      num[l++] = c;
    }
    l -= k;
    int j = 0;
    for (; j < l; ++j) {
      if (num[j] != '0') {
        break;
      }
    }
    if (j != l) {
      if (i != s) {
        return num.substr(j, l - j) + num.substr(i, s - i);
      } else {
        return num.substr(j, l - j);
      }
    } else {
      for (j = i; j < s; ++j) {
        if (num[j] != '0') {
          break;
        }
      }
      return j != s ? num.substr(j, s - j) : "0";
    }
    assert(false);
    return "";
  }
};

int main() {
  Solution sol;
  auto ret = sol.removeKdigits("1432219", 3); 
  std::cout << ret << std::endl;
}
