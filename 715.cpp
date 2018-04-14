#include <iostream>
#include <set>
#include <algorithm>

struct Range {
  int start, finish;
  Range(int s, int f) : start(s), finish(f) {}
};

struct RangeCompare {
  bool operator()(const Range & r1, const Range & r2) {
    return r1.finish < r2.finish;
  }
};

class RangeModule {
  using SetTy = std::set<Range, RangeCompare>;
  using ItorTy = SetTy::iterator;
  SetTy range_set;
  void output() {
    return;
    for (auto & i : range_set) {
      std::cout << i.start << ':' << i.finish << ' ';
    }
    std::cout << std::endl;
  }
public:
    RangeModule() {}
    
    void addRange(int left, int right) {
      auto after = range_set.lower_bound(Range(left, left));
      if (after == range_set.end() || after->start > right) {
        range_set.insert(Range(left, right));
        return;
      }
      left = std::min(after->start, left);
      while (after != range_set.end() && after->start <= right) {
        auto after1 = std::next(after);
        int right1 = after->finish;
        range_set.erase(after);
        after = after1;
        if (right <= right1) {
          right = right1;
          break;
        }
      }
      range_set.insert(after, Range(left, right));
    }
    
    bool queryRange(int left, int right) {
      auto after = range_set.lower_bound(Range(left, left));
      return after != range_set.end() && after->start <= left && after->finish >= right;
    }
    
    void removeRange(int left, int right) {
      auto after = range_set.lower_bound(Range(left, left));
      if (after == range_set.end() || after->start >= right) {
        return;
      }
      if (after->start < left) {
        range_set.insert(after, Range(after->start, left));
        if (after->finish == left) {
          return;
        }
      } else if (after->start >= right) {
        return;
      }
      while (after != range_set.end() && after->start <= right) {
        auto after1 = std::next(after);
        if (after->finish <= right) {
          range_set.erase(after);
          after = after1;
        } else {
          int right1 = after->finish;
          range_set.erase(after);
          range_set.insert(after1, Range(right, right1));
          break;
        }
      }
    }
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule obj = new RangeModule();
 * obj.addRange(left,right);
 * bool param_2 = obj.queryRange(left,right);
 * obj.removeRange(left,right);
 */
