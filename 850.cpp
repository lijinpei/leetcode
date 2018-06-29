#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

class Solution {
public:
  int rectangleArea(std::vector<std::vector<int>> &rectangles) {
    int n = rectangles.size();
    std::vector<int> rows(n * 2), cols(n * 2);
    rows.resize(0);
    cols.resize(0);
    for (auto & r : rectangles) {
      rows.push_back(r[0]);
      rows.push_back(r[2]);
      cols.push_back(r[1]);
      cols.push_back(r[3]);
    }
    auto func = [](std::vector<int> & vec) {
      std::sort(vec.begin(), vec.end());
      vec.resize(std::distance(vec.begin(), std::unique(vec.begin(), vec.end())));
    };
    func(rows);
    func(cols);
    auto rectangle_compare = [](const std::vector<int> & r1, const std::vector<int> & r2) {
      return r1[0] < r2[0];
    };
    std::sort(rectangles.begin(), rectangles.end(), rectangle_compare);
    auto transform = [](int & v, std::vector<int> & vec) {
      v = std::distance(vec.begin(), std::lower_bound(vec.begin(), vec.end(), v));
    };
    for (auto & r : rectangles) {
      transform(r[0], rows);
      transform(r[2], rows);
      transform(r[1], cols);
      transform(r[3], cols);
    }
    auto pq_compare = [](const std::vector<int> & r1, const std::vector<int> & r2) {
      return r1[2] > r2[2];
    };
    int rn = rows.size(), cn = cols.size();
    std::vector<int> cols_delta(cn - 1);
    for (int c = 0; c + 1 < cn; ++c) {
      cols_delta[c] = cols[c + 1] - cols[c];
    }
    std::vector<int> col_num(cn);
    using pq_node_t = std::vector<int>;
    std::priority_queue<pq_node_t, std::vector<pq_node_t>, decltype(pq_compare)> pq(pq_compare);
    int64_t ans = 0;
    int p = 0;
    auto update_area = [&](int r) {
      for (int c = 0, s = col_num[0]; c + 1 < cn; ++c, s += col_num[c]) {
        if (s) {
          ans += int64_t(cols_delta[c]) * int64_t(r);
        }
      }
    };
    //auto dump = [](const std::vector<int> & r) {
      //std::cout << r[0] << ' ' << r[1] << ' ' << r[2] << ' ' << r[3] << std::endl;
    //};
    for (int r = 0; r + 1 < rn; ++r) {
      // pop rectangles
      while (!pq.empty()) {
        const auto & top = pq.top();
        if (top[2] <= r) {
          --col_num[top[1]];
          ++col_num[top[3]];
          //std::cout << "pop ";
          //dump(top);
          //std::cout << std::endl;
          pq.pop();
        } else {
          break;
        }
      }
      // push rectangles
      while (p < n && rectangles[p][0] == r) {
        auto & r = rectangles[p];
        ++col_num[r[1]];
        --col_num[r[3]];
        //std::cout << "push ";
        //dump(rectangles[p]);
        //std::cout << std::endl;
        pq.push(std::move(rectangles[p]));
        ++p;
      }
      update_area(rows[r + 1] - rows[r]);
      //std::cout << ans << std::endl;
    }
    return ans % 1000000007;
  }
};

int main() {
  Solution sol;
  std::vector<std::vector<int>> input{{0,0,2,2},{1,0,2,3},{1,0,3,1}};
  std::cout << sol.rectangleArea(input) << std::endl;
}
