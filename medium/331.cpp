#include <string>

class Solution {
  class IsValidSerializationImpl {
    const std::string & preorder;
    const int n;
    int calc(int start, int end) {
      if (start > end) {
        return -1;
      }
      if (preorder[start] == '#') {
        return start + 2;
      }
      int s1 = start;
      for (; preorder[s1] != ','; ++s1) {
        continue;
      }
      ++s1;
      int res = calc(s1, end);
      if (res < 0) {
        return res;
      }
      int ret = calc(res, end);
      if (ret < 0) {
        return ret;
      }
      return ret;
    }
  public:
    IsValidSerializationImpl(const std::string & preorder) : preorder(preorder), n(preorder.size()) {
    }
    bool calc() {
      return calc(0, n + 1) == n + 1;
    }
  };
public:
  bool isValidSerialization(const std::string & preorder) {
    return IsValidSerializationImpl(preorder).calc();
  }
};
