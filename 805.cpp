#include <vector>
#include <numeric>
#include <set>
#include <functional>

class Solution {
public:
  bool splitArraySameAverage(std::vector<int> &A) {
    int n = A.size();
    int sum = std::accumulate(A.begin(), A.end(), 0);
    using EleT = std::pair<int, int>;
    std::set<EleT, std::greater<EleT>> set;
    for (auto a : A) {
      for (auto s : set) {
        set.emplace(s.first + 1, s.second + a);
      }
      set.emplace(1, a);
    }
    /*
    for (auto s : set) {
      std::cout << s << ' ';
    }
    std::cout << std::endl;
    */
    for (int i = 1, ie = n / 2; i <= ie; ++i) {
      int v1 = (sum * i) % n;
      if (v1) {
        continue;
      }
      int v2 = (sum * i) / n;
      if (set.find({i, v2}) != set.end()) {
        return true;
      }
    }
    return false;
  }
};
