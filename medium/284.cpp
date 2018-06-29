#include <vector>
// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
  struct Data;
  Data *data;

public:
  Iterator(const std::vector<int> &nums);
  Iterator(const Iterator &iter);
  virtual ~Iterator();
  // Returns the next element in the iteration.
  int next();
  // Returns true if the iteration has more elements.
  bool hasNext() const;
};

class PeekingIterator : public Iterator {
  bool peeked, peek_hasNext;
  int peek_result;
public:
  PeekingIterator(const std::vector<int> &nums) : Iterator(nums), peeked(false) {
  }

  // Returns the next element in the iteration without advancing the iterator.
  int peek() {
    if (peeked) {
      return peek_result;
    }
    peeked = true;
    peek_hasNext = Iterator::hasNext();
    return peek_result = Iterator::next();
  }

  // hasNext() and next() should behave the same as in the Iterator interface.
  // Override them if needed.
  int next() {
    if (peeked) {
      peeked = false;
      return peek_result;
    } else {
      return Iterator::next();
    }
  }

  bool hasNext() const {
    if (peeked) {
      return peek_hasNext;
    }
    return Iterator::hasNext();
  }
};
