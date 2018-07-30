#include <iostream>
#include <string>

class Solution {
public:
  std::string convert(const std::string &str1, int k) {
    int s = str1.size();
    std::string str2(s, '\0');
    int t = k + k - 2;
    int n = s / t, m = s % t, n2 = n + n;
    int s1, v1, v2;
    if (m > k) {
      v1 = 1;
      v2 = 2;
      s1 = k + k - m - 1;
    } else {
      v1 = 1;
      v2 = 0;
      s1 = m;
    }
    auto idx = [&](int p, int q) {
    };
    std::cout << s1 << ' ' << ' ' << v1 << ' ' << v2 << std::endl;
    int ss = 0;
    int i = 0;
    for (; ss + t < s; ++i) {
      int p1 = i;
      for (int j = 0; j < t; ++j) {
      std::cerr << p1 << ' ' << ss << std::endl;
      std::cout << str1 << std::endl;
        str2[p1] = str1[ss++];
        p1 += (j ? n2 : n) + (j < s1 ? v1 : v2);
      }
    }
    int p1 = i;
    for (int j = 0; j < m; ++j) {
      std::cerr << p1 << ' ' << ss << std::endl;
      str2[p1] = str1[ss++];
      p1 += (j ? n2 : n) + (j < s1 ? v1 : v2);
    }
    return str2;
  }
};

int main() {
  Solution sol;
  auto ret = sol.convert("PAYPALISHIRING", 3);
  std::cout << ret << ';' << std::endl;
}
