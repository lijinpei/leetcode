#include <string>
#include <vector>

class Solution {
public:
  std::vector<std::string> removeComments(std::vector<std::string> &source) {
    std::vector<std::string> ret;
    bool in_comment = false;
    std::string line1;
    for (const auto & line : source) {
      int s = line.size();
      for (int i = 0; i < s; ++i) {
        switch(line[i]) {
        case '*':
          if (in_comment) {
            if (i + 1 < s && line[i + 1] == '/') {
              ++i;
              in_comment = false;
            }
          } else {
            line1.push_back('*');
          }
          break;
        case '/':
          if (!in_comment) {
            if (i + 1 < s && line[i + 1] == '/') {
              goto next;
            }
            if (i + 1 < s && line[i + 1] == '*') {
              ++i;
              in_comment = true;
            } else {
              line1.push_back('/');
            }
          }
          break;
        default:
          if (!in_comment) {
            line1.push_back(line[i]);
          }
        }
      }
next:
      if (!line1.empty() && !in_comment) {
        ret.push_back(std::move(line1));
        line1 = "";
      }
    }
    return ret;
  }
};
