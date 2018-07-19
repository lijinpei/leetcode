#include <iostream>
#include <vector>
#include <string>

class Solution {
  void reverse(std::string & str) {
    for (int i = 0, j = str.size() - 1; i < j; ++i, --j) {
      std::swap(str[i], str[j]);
    }
  }

  void removeLeft(const std::string & str, int p, int cn, std::vector<std::string> & ret) {
    if (!cn) {
      ret.push_back(str);
      return;
    }
    int sz = str.size();
    for (; p < sz; ++p) {
      if ('(' == str[p]) {
        int p1 = p + 1;
        for (; p1 < sz; ++p1) {
          if (str[p1] != '(') {
            break;
          }
        }
        int cn1 = std::min(p1 - p, cn);
        for (int i = 0; i <= cn1; ++i) {
          removeLeft(str.substr(0, p1 - i) + str.substr(p1), p1 - i, cn - i, ret);
        }
        p = p1;
      }
    } 
  }

  void removeInvalidParentheses(std::string str, int first_l, int first_r, char c1, std::vector<std::string> & ret) {
    int cn = 0, sz = str.size();
    char c2 = c1 == '(' ? ')' : '(';
    for (int i = 0; i < sz; ++i) {
      char c = str[i];
      if (c == c1) {
        ++cn;
      }
      if (c == c2) {
        --cn;
      }
      if (cn >= 0) {
        continue;
      }
      for (; first_r <= i; ++first_r) {
        if (c2 == str[first_r]) {
          removeInvalidParentheses(str.substr(0, first_r) + str.substr(first_r + 1), first_l <= first_r ? first_l : first_l - 1, first_r, c1, ret);
          for (++first_r; first_r <= i; ++first_r) {
            if (str[first_r] != c2) {
              break;
            }
          }
        }
      }
      return;
    }
    if (cn == 0) {
      ret.push_back(str);
      return;
    }
    if (c1 == ')') {
      reverse(str);
      ret.push_back(str);
    } else {
      reverse(str);
      removeInvalidParentheses(str, 0, 0, c2, ret);
    }
  }
public:
  std::vector<std::string> removeInvalidParentheses(std::string str) {
    std::vector<std::string> ret;
    removeInvalidParentheses(str, 0, 0, '(', ret);
    return std::move(ret);
  }
};

int main() {
  Solution sol;
  sol.removeInvalidParentheses(")()(");
}
