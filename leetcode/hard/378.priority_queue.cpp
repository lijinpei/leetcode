#include <iostream>
#include <queue>
#include <vector>
#include <utility>

class Solution {
public:
  int kthSmallest(std::vector<std::vector<int>>& matrix, int k) {
    size_t s = matrix.size();
    using T = std::pair<int, int>;
    auto compare = [&](const T & v1, const T & v2) {
      return v1.first > v2.first;
    };
    std::vector<T> container;
    container.reserve(s);
    std::priority_queue<T, std::vector<T>, decltype(compare)> pq(compare, std::move(container));
    for (size_t i = 0; i < s; ++i) {
      pq.push(std::make_pair(matrix[i][0], i));
    }
    std::vector<int> pos(s, 1);
    for (int i = 1; i < k; ++i) {
      T m = pq.top();
      pq.pop();
      if (pos[m.second] < s) {
        pq.emplace(matrix[m.second][pos[m.second]++], m.second);
      }
      //std::cout << m.first << std::endl;
    }
    return pq.top().first;
  }
};
