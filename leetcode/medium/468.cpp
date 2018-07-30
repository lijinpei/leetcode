#include <iostream>
#include <string>

class Solution {
  static bool validIPv4Address(const std::string & IP) {
    int i = 0, s = IP.size();
    bool end_mark;

    auto getDec = [&]() {
      int j = i;
      for (int s1 = std::min(s, i + 3); j < s1 && IP[j] != '.'; ++j) {
        continue;
      }
      if ('0' == IP[i] && j != i + 1) {
        return false;
      }
      if (j == s) {
        end_mark = true;
      } else if (IP[j] == '.') {
        end_mark = false;
      } else {
        return false;
      }
      if (j == i) {
        return false;
      }
      for (int k = i, v = 0; k < j; ++k) {
        if (IP[k] < '0' || IP[k] > '9') {
          return false;
        }
        v = v * 10 + IP[k] - '0';
        if (v >= 256) {
          return false;
        }
      }
      i = j + 1;
      return true;
    };

    return getDec() && !end_mark && getDec() && !end_mark && getDec() &&
           !end_mark && getDec() && end_mark;
  }
  static bool validIPv6Address(const std::string & IP) {
    int p = 0, s = IP.size();
    bool end_mark;

    auto getHex = [&]() {
      int k = p;
      for (int s1 = std::min(s, p + 4); k < s1 && IP[k] != ':'; ++k) {
        continue;
      }
      if (k == s) {
        end_mark = true;
      } else if (IP[k] == ':') {
        end_mark = false;
      } else {
        return false;
      }
      if (k == p) {
        return false;
      }
      for (int j = p; j < k; ++j) {
        char ch = IP[j];
        if (ch >= '0' && ch <= '9') {
          continue;
        }
        if (ch >= 'a' && ch <= 'f') {
          continue;
        }
        if (ch >= 'A' && ch <= 'F') {
          continue;
        }
        return false;
      }
      p = k;
      return true;
    };

    for (int i = 0; i < 7; ++i) {
      if (!getHex() || end_mark) {
        return false;
      }
      ++p;
    }
    return getHex() && end_mark;
  }
public:
  std::string validIPAddress(const std::string &IP) {
    return validIPv4Address(IP) ? "IPv4"
                                : validIPv6Address(IP) ? "IPv6" : "Neither";
  }
};

int main() {
  Solution sol;
  //std::cout << sol.validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334");
  //std::cout << sol.validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334:");
  //std::cout << sol.validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334");
  //std::cout << sol.validIPAddress("2001:0db8:85a3:00000:0:8A2E:0370:7334");
  std::cout << sol.validIPAddress("192.0.0.1");
}
