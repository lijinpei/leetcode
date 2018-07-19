#include <vector>
#include <string>
#include <climits>

class Solution {
  class SolutionImpl {
    const std::string & num;
    int64_t target;
    std::size_t num_sz;
    std::vector<std::string> ret;
    void search(int64_t sum, int64_t mul, std::size_t p, const std::string & prefix) {
      if (num[p] == '0') {
        if (p == num_sz - 1) {
          if (sum == target) {
            ret.push_back(prefix + "0");
          }
          return;
        }
        const std::string & s1 = num.substr(p, 1);
        search(sum, 1, p + 1, prefix + s1 + "+");
        search(sum, -1, p + 1, prefix + s1 + "-");
        search(sum, 0, p + 1, prefix + s1 + "*");
        return;
      }
      int64_t v = 0;
      for (std::size_t i = p + 1; i < num_sz; ++i) {
        const std::string & s1 = num.substr(p, i - p);
        v = v * 10 + num[i - 1] - '0';
        if (v > INT_MAX) break;
        search(sum + mul * v, 1, i, prefix + s1 + '+');
        search(sum + mul * v, -1, i, prefix + s1 + '-');
        search(sum, mul * v, i, prefix + s1 + '*');
      }
      const std::string & s1 = num.substr(p, num_sz);
      v = v * 10 + num[num_sz - 1] - '0';
      if (sum + mul * v == target) {
        ret.push_back(prefix + s1);
      }
    }
  public:
    SolutionImpl(const std::string & num, int target) : num(num), target(target), num_sz(num.size()), ret() {
    }
    std::vector<std::string> calc() {
      if (num_sz) {
        search(0, 1, 0, "");
      }
      return std::move(ret);
    }
  };
public:
  std::vector<std::string> addOperators(const std::string & num, int target) {
    return SolutionImpl(num, target).calc();
  }
};

int main() {
  Solution sol;
  sol.addOperators("3456237490", 9191);
}
