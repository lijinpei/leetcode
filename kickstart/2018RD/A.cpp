#include <vector>
#include <map>
#include <utility>
#include <limits>
#include <iostream>

class Solution {
  int64_t N, O, D;
  std::vector<int64_t> & S;
public:
  Solution(int64_t N, int64_t O, int64_t D, std::vector<int64_t> & S) : N(N), O(O), D(D), S(S) {}
  std::pair<bool, int64_t> calc() {
    std::map<int64_t, int64_t> sums;
    std::vector<std::map<int64_t, int64_t>::iterator> sums_pos;
    sums_pos.reserve(N + 1);
    sums_pos.push_back(sums.emplace(0, 1).first);
    bool has_ans = false;
    int64_t ans = std::numeric_limits<int64_t>::min();
    int64_t sum = 0;
    auto update_ans = [&]() {
      auto itor = sums.lower_bound(sum - D);
      if (itor != sums.end()) {
        has_ans = true;
        //std::cout << "sum : " << sum << ' ' << itor->first << std::endl;
        int64_t v1 = sum - itor->first;
        if (v1 > ans) {
          ans = v1;
        }
      }
    };
    auto del = [&](int p) {
      auto itor = sums_pos[p];
      if (itor->second > 1) {
        --itor->second;
      } else {
        sums.erase(itor);
      }
    };
      //std::cout << "ans: " << ans << std::endl;
    for (int64_t i = 1, o = 0, p = 0; i <= N; ++i) {
      int64_t s = S[i];
      sum += s;
      if (s & 1) {
        ++o;
        if (o > O) {
          del(p++);
          while (p < i) {
            int s = S[p];
            if (s & 1) {
              break;
            }
            del(p++);
          }
        }
        if (O != 0) {
          update_ans();
        }
      } else {
        update_ans();
      }
      auto res = sums.emplace(sum, 1);
      if (!res.second) {
        ++(res.first->second);
      }
      sums_pos.push_back(res.first);
      //std::cout << "ans: " << ans << std::endl;
    }
    return {has_ans, ans};
  }
};

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; ++t) {
    int64_t N, O, D;
    std::vector<int64_t> input;
    std::cin >> N >> O >> D;
    input.reserve(N + 1);
    input.push_back(0);
    int64_t x1, x2, a, b, c, m, l;
    std::cin >> x1 >> x2 >> a >> b >> c >> m >> l;
    input.push_back(x1 + l);
    input.push_back(x2 + l);
    for (int64_t i = 2; i < N; ++i) {
      int64_t x3 = (a * x2 + b * x1 + c) % m;
      input.push_back(x3 + l);
      x1 = x2;
      x2 = x3;
    }
    Solution sol(N, O, D, input);
    auto ans = sol.calc();
    std::cout << "Case #" << (t + 1) << ": ";
    if (ans.first) {
      std::cout << ans.second << std::endl;
    } else {
      std::cout << "IMPOSSIBLE\n";
    }
  }
}
