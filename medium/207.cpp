#include <algorithm>
#include <vector>
#include <utility>

class Solution {
  class CanFinishImpl {
    int numCourses;
    std::vector<std::pair<int, int>> prerequisites;
    std::vector<int> pre_num;
    std::vector<std::vector<int>> pre;
    bool calc(int c) {
      pre_num[c] = 1;
      for (auto p : pre[c]) {
        int pv = pre_num[p];
        if (pv == 1) {
          return false;
        }
        if (pv == 2) {
          continue;
        }
        if (!calc(p)) {
          return false;
        }
      }
      pre_num[c] = 2;
      return true;
    }
  public:
    CanFinishImpl(int numCourses, std::vector<std::pair<int, int>> & prerequisites) : numCourses(numCourses), prerequisites(prerequisites), pre_num(numCourses), pre(numCourses) {
      for (auto & p : prerequisites) {
        ++pre_num[p.first];
      }
      for (int i = 0; i < numCourses; ++i) {
        pre[i].reserve(pre_num[i]);
      }
      for (auto & p : prerequisites) {
        pre[p.first].push_back(p.second);
      }
      std::fill(pre_num.begin(), pre_num.end(), 0);
    }
    bool calc() {
      for (int i = 0; i < numCourses; ++i) {
        if (pre_num[i]) {
          continue;
        }
        if (!calc(i)) {
          return false;
        }
      }
      return true;
    }
  };
public:
  bool canFinish(int numCourses, std::vector<std::pair<int, int>>& prerequisites) {
    return CanFinishImpl(numCourses, prerequisites).calc();
  }
};
