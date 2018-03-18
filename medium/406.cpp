#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

bool my_comp(const std::pair<int, int> & p1, const std::pair<int, int> & p2) {
  return p1.first > p2.first || (p1.first == p2.first && p1.second < p2.second);
}

class Solution {
public:
  std::vector<std::pair<int, int>> reconstructQueue(std::vector<std::pair<int, int>> & people) {
    std::sort(people.begin(), people.end(), my_comp);
    int s = people.size();
    std::vector<int> index;
    for (int i = 0; i < s; ++i) {
      index.insert(index.begin() + people[i].second, i);
    }
    std::vector<std::pair<int, int>> ret(s);
    for (int i = 0; i < s; ++i) {
      ret[i] = people[index[i]];
    }
    return ret;
  }
};

int main() {
  std::vector<std::pair<int, int>> input{{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}};
  Solution sol;
  auto ret = sol.reconstructQueue(input);
  for (const auto & c : ret) {
    std::cout << c.first << ' ' << c.second << std::endl;
  }
}
