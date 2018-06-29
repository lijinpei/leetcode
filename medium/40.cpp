#include <iostream>
#include <algorithm>
#include <vector>

class Solution {
  std::vector<std::vector<int>> ret;
  std::vector<int> tmp, *cand, *cou;
  int n, un;
  void search(int p, int target, int left) {
    if (!target) {
      ret.push_back(tmp);
      return;
    }
    if (p == un) {
      return;
    }
    int v = (*cand)[p], m = (*cou)[p];
    left -= m;
    int i;
    for (i = 0; i <= m; ++i) {
      if (target < 0) {
        break;
      }
      search(p + 1, target, left);
      tmp.push_back(v);
      target -= v;
    }
    tmp.resize(tmp.size() - i);
  }
public:
  std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
    n = candidates.size();
    std::sort(candidates.begin(), candidates.end());
    std::vector<int> count(n);
    un = 0;
    {
      int v = candidates[0], m = 1;
      for (int p = 1; p < n; ++p) {
        if (candidates[p] != v) {
          count[un] = m;
          candidates[un++] = v;
          v = candidates[p];
          m = 1;
        } else {
          ++m;
        }
      }
      count[un] = m;
      candidates[un] = v;
      ++un;
      candidates.resize(un);
      count.resize(un);
      //for (int v : candidates) {
        //std::cout << v << ' ';
      //}
      //std::cout << std::endl;
      //for (int v : count) {
        //std::cout << v << ' ';
      //}
      //std::cout << std::endl;
    }
    tmp.clear();
    ret.clear();
    cand = &candidates;
    cou = &count;
    search(0, target, n);
    return std::move(ret);
  }
};

int main() {
  Solution sol;
  std::vector<int> input{10,1,2,7,6,1,5};
  auto ret = sol.combinationSum2(input, 8);
  for (auto & r : ret) {
    for (int v : r) {
      std::cout << v << ' ';
    }
    std::cout << std::endl;
  }
}
