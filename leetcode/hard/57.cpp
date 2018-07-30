#include <iostream>
#include <vector>
#include <algorithm>

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

bool end_comp(const Interval & i1, const Interval & i2) {
  return i1.end < i2.end;
}

class Solution {
public:
  std::vector<Interval> insert(const std::vector<Interval> &intervals,
                               const Interval &newInterval) {
    int s = intervals.size();
    if (!s) {
      return {newInterval};
    }
    int start = newInterval.start, end = newInterval.end;
    // find the first internal i such that i.end >= start
    //int p1 = std::distance(intervals.begin(), std::lower_bound(intervals.begin(), intervals.end(), Interval(start, start), end_comp));
    int p1 = 0;
    for (;p1 < s && intervals[p1].end < start; ++p1) {
      continue;
    }
    int p2 = p1, l = end;
    for (;p2 < s && intervals[p2].start <= l; ++p2) {
      l = std::max(l, intervals[p2].end);
    }
    int ns = p1 + (s - p2) + 1;
    std::vector<Interval> ret(ns);
    std::copy(intervals.begin(), intervals.begin() + p1, ret.begin());
    if (p1 != p2) {
      start = std::min(start, intervals[p1].start);
      end = std::max(end, intervals[p2 - 1].end);
    }
    ret[p1] = {start, end};
    std::copy(intervals.begin() + p2, intervals.end(), ret.begin() + p1 + 1);
    return ret;
  }
};

int main() {
  Solution sol;
//  std::vector<Interval> input{{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
//  auto ret = sol.insert(input, {4, 9});
  std::vector<Interval> input{{1, 5}};
  auto ret = sol.insert(input, {5, 7});
  for (const auto & i : ret) {
    std::cout << i.start << ' ' << i.end << std::endl;
  }
}
