#include <iostream>
#include <queue>
#include <vector>
#include <utility>

class Solution {
public:
  int kthSmallest(std::vector<std::vector<int>>& matrix, int k) {
    size_t s = matrix.size();
    using T = std::pair<int, int>;
    std::vector<int> pos(s, 1);
    std::vector<T> heap(s);
    for (size_t i = 0; i < s; ++i) {
      heap[i].first = matrix[i][0];
      heap[i].second = i;
    }
    while (--k) {
      T m = heap[0];
      /*
      std::cout << m.first << ' ' << heap.size() << std::endl;
      for (auto v : heap) {
        std::cout << v.first << ' ' << v.second << ' ';
      }
      std::cout << std::endl;
      */
      if (pos[m.second] < s) {
        heap[0].first = matrix[m.second][pos[m.second]++];
      } else {
        heap[0] = heap.back();
        heap.pop_back();
      }
      int i = 0, s = heap.size();
      while (i < s) {
        int i1 = 2 * i + 1, i2 = i1 + 1, mi;
        if (i1 >= s) {
          break;
        }
        if (i2 >= s || heap[i1].first <= heap[i2].first) {
          mi = i1;
        } else {
          mi = i2;
        }
        if (heap[mi].first >= heap[i].first) {
          break;
        }
        std::swap(heap[i], heap[mi]);
        i = mi;
      }
    }
    return heap[0].first;
  }
};

int main() {
  using V = std::vector<int>;
  V v1{1, 4, 7, 11, 15};
  V v2{2, 5, 8, 12, 19};
  V v3{3, 6, 9, 16, 22};
  V v4{10, 13, 14, 17, 24};
  V v5{18, 21, 23, 26, 30};
  std::vector<V> vv{v1, v2, v3, v4, v5};
  Solution sol;
  std::cout << sol.kthSmallest(vv, 5) << std::endl;
}
