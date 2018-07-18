#include <string>
#include <vector>

const int num[] = {3, 3, 3, 3, 3, 4, 3, 4};
const char *const str[] = {"abc", "def",  "ghi", "jkl",
                                    "mno", "pqrs", "tuv", "wxyz"};
class Solution {

public:
  std::vector<std::string> letterCombinations(const std::string &digits) {
    int ans_l = digits.size();
    if (!ans_l) {
      return {};
    }
    int ans_num = 1;
    for (auto c : digits) {
      ans_num *= num[c - '2'];
    }
    std::vector<std::string> ret(ans_num, std::string(ans_l, ' '));
    int c = digits[0] - '2';
    ans_num = num[c];
    for (int i = 0; i < ans_num; ++i) {
      ret[i][0] = str[c][i];
    }
    for (int d = 1; d < ans_l; ++d) {
      int c = digits[d] - '2';
      char ch = str[c][0];
      for (int i = 0; i < ans_num; ++i) {
        ret[i][d] = ch;
      }
      int p = ans_num;
      for (int i = 1; i < num[c]; ++i) {
        char ch = str[c][i];
        for (int j = 0; j < ans_num; ++j) {
          for (int d1 = 0; d1 < d; ++d1) {
            ret[p][d1] = ret[j][d1];
          }
          ret[p++][d] = ch;
        }
      }
      ans_num = p;
    }
    return ret;
  }
};

