#include <vector>
#include <algorithm>

class Solution {
  static constexpr int max_age = 120;
public:
    int numFriendRequests(std::vector<int>& ages) {
      std::vector<int> age_num(max_age + 1);
      for (auto a : ages) {
        ++age_num[a];
      }
      for (int i = 1; i <= max_age; ++i) {
        age_num[i] += age_num[i - 1];
      }
      int ans = 0;
      for (int a = 15; a <= max_age; ++a) {
        ans += (age_num[a] - age_num[a - 1]) * (age_num[a] - age_num[a / 2 + 7] - 1);
      }
      return ans;
    }
};
