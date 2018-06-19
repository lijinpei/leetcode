#include <string>
#include <vector>

class Solution {
public:
  std::string shiftingLetters(std::string S, std::vector<int>& shifts) {
    unsigned total_shift = 0;
    for (int s = shifts.size() - 1; s >= 0; --s) {
      total_shift += shifts[s];
      total_shift %= 26;
      char c = (S[s] - 'a' + total_shift);
      if (c >= 26) {
        c -= 26;
      }
      S[s] = c + 'a';
    }
    return S;
  }
};
