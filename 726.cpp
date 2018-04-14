#include <cctype>
#include <string>
#include <forward_list>
#include <unordered_map>
#include <vector>
#include <algorithm>

class Solution {
public:
  std::string countOfAtoms(const std::string & formula) {
    std::unordered_map<std::string, int> count;
    std::forward_list<int> mult;
    int current_num = 1, total_number = 1;
    for (int s = formula.size() - 1; s >= 0; --s) {
      int s1;
      if (std::isdigit(formula[s])) {
        s1 = s - 1;
        for (; s1 >= 0; --s1) {
          if (!std::isdigit(formula[s1])) {
            break;
          }
        }
        current_num = std::stoi(formula.substr(s1 + 1, s - s1));
        s = s1 + 1;
        continue;
      }
      if (formula[s] == ')') {
        mult.push_front(current_num);
        total_number *= current_num;
        current_num = 1;
        continue;
      }
      if (formula[s] == '(') {
        total_number /= *mult.begin();
        mult.pop_front();
        continue;
      }
      s1 = s;
      for (; s >= 0 && !std::isupper(formula[s]); --s) {
        continue;
      }
      count[formula.substr(s, s1 - s + 1)] += current_num * total_number;
      current_num = 1;
    }
    std::vector<std::pair<std::string, int>> vec(count.begin(), count.end());
    std::sort(vec.begin(), vec.end());
    std::string ret;
    for (auto & kv : vec) {
      ret += kv.first;
      if (kv.second != 1) {
        ret += std::to_string(kv.second);
      }
    }
    return ret;
  }
};
