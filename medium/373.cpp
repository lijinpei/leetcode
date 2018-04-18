#include <queue>
#include <utility>
#include <vector>

class Solution {
public:
  std::vector<std::pair<int, int>>
  kSmallestPairs(std::vector<int> &nums1, std::vector<int> &nums2, int k) {
    int n1 = nums1.size(), n2 = nums2.size();
    if (!n1 || !n2) {
      return {};
    }
    std::vector<std::pair<int, int>> pq_storage(n1), ret;
    ret.reserve(k);
    for (int i = 0; i < n1; ++i) {
      pq_storage[i] = {i, 0};
    }
    auto pq_compare = [&](const std::pair<int, int> &p1,
                          const std::pair<int, int> &p2) {
      auto v = [&](const std::pair<int, int> &p) {
        return nums1[p.first] + nums2[p.second];
      };
      return v(p1) >= v(p2);
    };
    std::priority_queue<std::pair<int, int>, decltype(pq_storage),
                        decltype(pq_compare)>
        pq(pq_compare, pq_storage);
    while (k--) {
      if (pq.empty()) {
        break;
      }
      auto p = pq.top();
      ret.emplace_back(nums1[p.first], nums2[p.second]);
      pq.pop();
      if (p.second + 1 < n2) {
        pq.emplace(p.first, p.second + 1);
      }
    }
    return ret;
  }
};

int main() { Solution sol;
  std::vector<int> v1{1, 7, 11}, v2{2, 4, 6};
  auto ret = sol.kSmallestPairs(v1, v2, 3);
}
