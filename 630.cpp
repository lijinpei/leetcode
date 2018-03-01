#include <vector>
#include <utility>
#include <queue>
#include <algorithm>

class Solution {
public:
  int scheduleCourse(std::vector<std::vector<int>> &courses_) {
    int s = courses_.size();
    using T = std::pair<int, int>;
    std::vector<T> courses(s);
    for (int i = 0; i < s; ++i) {
      courses[i] = T(courses_[i][0], courses_[i][1]);
    }
    auto course_compare = [](const T &n1, const T &n2) {
      return n1.second < n2.second;
    };
    std::sort(courses.begin(), courses.end(), course_compare);
    std::vector<int> pq_container;
    pq_container.reserve(s);
    std::priority_queue<T, decltype(pq_container), std::less<int>> pq(std::less<int>(), pq_container);
    int sum = 0;
    for (int i = 0; i < s; ++i) {
      int v1 = courses[i].first, v2 = courses[i].second;
      sum += v1;
      pq.push(v1);
      while (sum > v2) {
        sum -= pq.top();
        pq.pop();
      }
    }
    return pq.size();
  }
};
