#include <iostream>
#include <set>
#include <vector>

struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

struct IntervalCompare {
  bool operator()(const Interval & i1, const Interval & i2) {
    return i1.start < i2.start;
  }
};

class SummaryRanges {
  using SetTy = std::set<Interval, IntervalCompare>;
  using ItorTy = SetTy::iterator;
  SetTy interval_set;
public:
  /** Initialize your data structure here. */
  SummaryRanges() {}
  void addNum(int val) {
    Interval ni(val, val);
    ItorTy after = interval_set.upper_bound(ni), before;
    bool merge_after, merge_before;
    if (after != interval_set.begin() && !interval_set.empty()) {
      before = std::prev(after);
      merge_before = val <= before->end + 1;
    } else {
      merge_before = false;
    }
    if (after != interval_set.end()) {
      merge_after = val >= after->start - 1;
    } else {
      merge_after = false;
    }
    if (merge_before && merge_after) {
      const_cast<int&>(before->end) = after->end;
      interval_set.erase(after);
    } else if (merge_before) {
      const_cast<int&>(before->end) = std::max(before->end, val);
    } else if (merge_after) {
      const_cast<int&>(after->start) = std::min(after->start, val);
    } else {
      interval_set.insert(ni);
    };
  }
  std::vector<Interval> getIntervals() {
    return {interval_set.begin(), interval_set.end()};
  }
};
