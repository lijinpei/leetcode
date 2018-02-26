#include <set>
#include <iterator>

class MedianFinder {
  std::multiset<int> mset;
  std::multiset<int>::iterator itor;

public:
  /** initialize your data structure here. */
  MedianFinder() : itor(mset.end()) {}

  void addNum(int num) {
    mset.insert(num);
    int s = mset.size();
    if (1 == s) {
      itor = mset.begin();
      return;
    }
    if (s & 1) {
      if (num >= *itor) {
        ++itor;
      }
    } else {
      if (num < *itor) {
        --itor;
      }
    }
  }

  double findMedian() {
    if (mset.size() & 1) {
      return *itor;
    }
    return 0.5 * (*itor + *std::next(itor));
  }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder obj = new MedianFinder();
 * obj.addNum(num);
 * double param_2 = obj.findMedian();
 */
