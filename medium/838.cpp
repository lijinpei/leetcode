#include <string>

class Solution {
public:
  std::string pushDominoes(std::string dominoes) {
    int s = dominoes.size();
    if (!s) {
      return dominoes;
    }
    int lp = 0;
    char lc = dominoes[0];
    for (int i = 1; i < s; ++i) {
      char c = dominoes[i];
      if (c == '.') {
        continue;
      }
      if (c == 'L') {
        if (lc == 'R') {
          int i1 = i - 1, j1 = lp + 1;
          while (j1 < i1) {
            dominoes[j1++] = 'R';
            dominoes[i1--] = 'L';
          }
        } else {
          for (int j = lp; j < i; ++j) {
            dominoes[j] = 'L';
          }
        }
      } else if (lc == 'R') {
        for (int j = lp + 1; j < i; ++j) {
          dominoes[j] = 'R';
        }
      }
      lp = i;
      lc = c;
    }
    if (lc == 'R') {
      for (++lp; lp < s; ++lp) {
        dominoes[lp] = 'R';
      }
    }
    return dominoes;
  }
};
