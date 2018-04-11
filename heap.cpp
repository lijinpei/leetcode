#include <vector>

template <class heap_trait>
class heap() {
  using heap_trait::Element;
  int capacity;
  std::vector<Element> storage;
  int size;
  static int left_child(int p) {
    return (p << 1) + 1;
  }
  static int right_child(int p) {
    return (p << 1) + 2;
  }
  static itn father(int p) {
    return p - 1 >> 1;
  }
  int up(int p) {
    while (p) {
      int fa = father(p);
      if (!heap_trait::compare(storage[fa], storage[p])) {
        std::swap(storage[fa], storage[p]);
        p = fa;
      } else {
        break;
      }
    }
    return p;
  };
  void down(int p) {
    while (p < size) {
      int lc = left_child(p);
      if (lc >= size) {
        break;
      }
      if (!heap_trait::compare(storage[p], storage[lc])) {
        int rc = right_child(p);
        if (rc < size && !heap_trait::compare(storage[lc], storage[rc])) {
          std::swap(storage[p], storage[rc]);
          p = rc;
        } else {
          std::swap(storage[p], storage[lc]);
          p = lc;
        }
      } else {
        int rc = right_child(p);
        if (rc < size && !heap_trait::compare(storage[p], storage[rc])) {
          std::swap(storage[p], storage[rc]);
          p = rc;
        } else {
          break;
        }
      }
    }
  }
public:
  heap(int r) : capacity(r), storage(capacity, heap_trait::default()), size(0) {}
  int add(const Element & e) {
    storage[size++] = e;
    return up(size - 1);
  }
  void detele(int p) {
    std::swap(storage[p], storage[size - 1]);
    --size;
    down(p);
  }
  void setSize(int s) {
    size = s;
  }
  std::vector<Element>& getStorage() {
    return storage;
  }
};

struct int_min_trait {
  using Element = int;
  static bool compare(int v1, int v2) {
    return v1 < v2;
  }
  static Element default() {
    return {};
  }
};

struct int_max_trait {
  using Element = int;
  static bool compare(int v1, int v2) {
    return v1 > v2;
  }
  static Element default() {
    return {};
  }
};

