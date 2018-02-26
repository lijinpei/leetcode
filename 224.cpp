#include <string>
#include <iostream>
#include <stack>
#include <vector>

class Solution {
  enum OperatorKind {
    OK_Add,
    OK_Sub,
    OK_LeftParentheses,
    OK_RightParentheses
  };
public:
  int calculate(const std::string & str) {
    int ss = 0, ss1 = 0;
    for (const auto & c : str) {
      if (c == ')') {
        --ss1;
      } else if (c == '(') {
        ++ss1;
        ss = std::max(ss, ss1);
      }
    }
    using StackNode = std::pair<int, OperatorKind>;
    std::vector<StackNode> stack_storage;
    std::stack<StackNode, decltype(stack_storage)> st;
    int cv = 0, nv;
    OperatorKind co = OK_Add;
    int p = 0;
    int const s = str.size();
    char c;
    auto next_non_empty = [&]() {
      while (p < s) {
        if ((c = str[p]) != ' ') {
          break;
        }
        ++p;
      }
    };
    auto next_val_impl = [&]() {
      nv = c - '0';
      ++p;
      while (p < s) {
        c = str[p];
        if (c >= '0' && c <= '9') {
          nv = nv * 10 + c - '0';
        } else {
          return;
        }
        ++p;
      }
    };
    // return next value and handle stack
    auto next_val = [&]() {
again:
      if (p == s) {
        nv = 0;
        return;
      }
      next_non_empty();
      if (c == '(') {
        ++p;
        st.emplace(cv, co);
        cv = 0;
        co = OK_Add;
        goto again;
      } else {
        next_val_impl();
      }
    };
    // return next '+'/'-' and handle stack
    auto next_op= [&]() {
again:
      if (p == s) {
        co = OK_Add;
        return;
      }
      next_non_empty();
      if (c == ')') {
        ++p;
        auto tos = st.top();
        st.pop();
        cv = tos.first + (tos.second == OK_Add ? cv : -cv);
        goto again;
      } else {
        ++p;
        co = (c == '+' ? OK_Add : OK_Sub);
      }
    };
    while (p < s) {
      next_val();
      if (co == OK_Add) {
        cv += nv;
      } else {
        cv -= nv;
      }
      next_op();
    }
    return cv;
  }
};

int main() {
  std::string s;
  Solution sol;
  while (getline(std::cin, s)) {
    std::cout << sol.calculate(s) << std::endl;
  }
}
