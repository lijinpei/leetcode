#include <iostream>
#include <string>

class Solution {
public:
  std::string numberToWords(int num) {
    if (!num) {
      return "Zero";
    }
    auto  to_val = [](int v) -> std::string {
      std::string arr1[21] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
      std::string arr2[] = {"Twenty", "Thirty",  "Forty", "Fifty",
                            "Sixty",  "Seventy", "Eighty", "Ninety"};
      int v1 = v / 100, v2 = v / 10 % 10, v3 = v % 10, v4 = v % 100;
      std::string ret;
      bool b = false;
      if (v1) {
        ret = ret + arr1[v1] + " " + "Hundred";
        b = true;
      }
      if (v2 >= 2) {
        ret = ret + (b ? " " : "") + arr2[v2 - 2];
        b = true;
      }
      if (v4 < 20 && v4) {
        ret = ret + (b ? " " : "") + arr1[v4];
      } else if (v3) {
        ret = ret + (b ? " " : "") + arr1[v3];
      }
      return ret;
    };
    std::string base_str[4] = {"", " Thousand", " Million", " Billion"};
    int base_val[4];
    for (int i = 0; i < 4; ++i) {
      base_val[i] = num % 1000;
      num /= 1000;
    }
    std::string ret;
    bool b = false;
    for (int i = 3; i >= 0; --i) {
      if (base_val[i]) {
        if (b) {
          ret += " ";
        }
        b = true;
        ret += to_val(base_val[i]);
        ret += base_str[i];
      }
    }
    return ret;
  }
};

int main() {
  Solution sol;
  auto ret = sol.numberToWords(12345);
  std::cout << ret << std::endl;
}
