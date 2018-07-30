#include <vector>
#include <stack>
#include <string>
#include <functional>

class Solution {
public:
  int evalRPN(std::vector<std::string>& tokens) {
    std::stack<int> vals;
    auto calc = [&](auto && f) {
      int v2 = vals.top();
      vals.pop();
      int v1 = vals.top();
      vals.pop();
      vals.push(f(v1, v2));
    };
    for (auto & token : tokens) {
      switch(token[0]) {
      case '+':
        calc(std::plus<int>{});
        break;
      case '*':
        calc(std::multiplies<int>{});
        break;
      case '/':
        calc(std::divides<int>{});
        break;
      case '-':
        if (token.size() == 1) {
          calc(std::minus<int>{});
          break;
        }
      default:
        vals.push(std::stoi(token));
      }
    }
    return vals.top();
  }
};
