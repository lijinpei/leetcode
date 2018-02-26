#include <iostream>
#include <vector>
#include <utility>

class Solution {
public:
  std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
    int s = nums.size();
    std::vector<int> ret(s ? s - k + 1 : 0);
    if (!s) {
      return ret;
    }
    using T = std::pair<int, int>;
    std::vector<T> dq(s);
    int tail = 0;
    dq[0] = T(nums[0], 0);
    for (int i = 1; i < k; ++i) {
      int v = nums[i];
      while (tail >= 0 && dq[tail].first <= v) {
        --tail;
      }
      dq[++tail] = T(v, i);
    }
    int head = 0;
    ret[0] = dq[0].first;
    for (int i = k; i < s; ++i) {
      int v = nums[i];
      while (tail >= head && dq[tail].first <= v) {
        --tail;
      }
      dq[++tail] = T(v, i);
      int p = i - k;
      while (tail > head && dq[head].second <= p) {
        ++head;
      }
      ret[p + 1] = dq[head].first;
    }
    return ret;
  }
};

int main() {
  Solution sol;
  std::vector<int> input{1, 3, 1, 2, 0, 5};
  auto ret = sol.maxSlidingWindow(input, 3);
  for (auto v : ret) {
    std::cout << v << ' ';
  }
  std::cout << std::endl;
}
