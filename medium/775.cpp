#include <algorithm>
#include <vector>
/*
class Solution {
public:
  bool isIdealPermutation(const std::vector<int> &A) {
    int n = A.size();
    if (n <= 2) {
      return true;
    }
    int mv = A[n - 1];
    for (int i = n - 2; i > 0; --i) {
      if (A[i - 1] > mv) {
        return false;
      }
      mv = std::min(A[i], mv);
    }
    return true;
  }
};
*/
class Solution {
public:
  bool isIdealPermutation(const std::vector<int> &A) {
    int n = A.size();
    if (n <= 2) {
      return true;
    }
    int mv = A[0];
    for (int i = 1, n1 = n - 1; i < n1; ++i) {
      if (A[i + 1] < mv) {
        return false;
      }
      mv = std::max(A[i], mv);
    }
    return true;
  }
};
