#include <string>
#include <numeric>

class Solution {
public:
  int findSubstringInWraproundString(const std::string & p) {
    if (p.empty()) {
      return 0;
    }
    int arr[26] = {};
    int c = p.back() - 'a';
    arr[c] = 1;
    int l = 1;
    for (int i = p.size() - 2; i >= 0; --i) {
      int c1 = p[i] - 'a';
      if ((c1 == 25 && c == 0) || c1 + 1 == c) {
        ++l;
      } else {
        l = 1;
      }
      if (l > arr[c1]) {
        arr[c1] = l;
      }
      c = c1;
    }
    return std::accumulate(arr, arr + 26, 0);
  }
};
