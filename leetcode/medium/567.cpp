#include <string>

class Solution {
public:
  bool checkInclusion(const std::string & str1, const std::string & str2) {
    int s1 = str1.size(), s2 = str2.size();
    if (s1 > s2) {
      return false;
    }
    int count[26] = {};
    int mismatch = 0;
    auto add = [&](char c_) {
      short c = c_ - 'a';
      if (!count[c]) {
        ++mismatch;
      } else if (-1 == count[c]) {
        --mismatch;
      }
      ++count[c];
    };
    auto sub = [&](char c_) {
      short c = c_ - 'a';
      if (!count[c]) {
        ++mismatch;
      } else if (1 == count[c]) {
        --mismatch;
      }
      --count[c];
    };
    for (auto c : str1) {
      add(c);
    }
    for (int i = 0; i < s1; ++i) {
      sub(str2[i]);
    }
    if (!mismatch) {
      return true;
    }
    for (int i = s1; i < s2; ++i) {
      add(str2[i - s1]);
      sub(str2[i]);
      if (!mismatch) {
        return true;
      }
    }
    return false;
  }
};
