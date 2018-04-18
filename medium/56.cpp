#include <algorithm>
#include <vector>

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
  std::vector<Interval> merge(std::vector<Interval> &intervals) {
    auto my_compare = [](const Interval & i1, const Interval & i2) {
      return i1.start < i2.start;
    };
    std::sort(intervals.begin(), intervals.end(), my_compare);
    int n = intervals.size();
    if (!n) {
      return {};
    }
    std::vector<Interval> ret;
    ret.reserve(n);
    Interval itl = intervals[0];
    for (int i = 1; i < n; ++i) {
      Interval itl1 = intervals[i];
      if (itl1.start <= itl.end) {
        itl.end = std::max(itl.end, itl1.end);
      } else {
        ret.push_back(itl);
        itl = itl1;
      }
    }
    ret.push_back(itl);
    return ret;
  }
};
