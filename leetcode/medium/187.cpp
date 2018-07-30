#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
  std::vector<std::string> findRepeatedDnaSequences(std::string str) {
    std::unordered_map<std::string, int> map;
    std::vector<std::string> ret;
    int s = str.size();
    for (int i = 0, ie = s - 9; i < ie; ++i) {
      auto & v = map[str.substr(i, 10)];
      ++v;
      if (2 == v) {
        ret.emplace_back(str.substr(i, 10));
      }
    }
    return ret;
  }
};
