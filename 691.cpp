/* TODO: potimize this program to sun within 35ms */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Sticker {
  int num[26];
  Sticker(const std::string & str) {
    std::fill(num, num + 26, 0);
    for (auto c : str) {
      ++num[c - 'a'];
    }
  }
  Sticker() {}
  bool feasible(const Sticker & rhs) const {
    for (int i = 0; i < 26; ++i) {
      if (rhs.num[i] && !num[i]) {
        return false;
      }
    }
    return true;
  }
  operator bool() const {
    for (int i = 0; i < 26; ++i) {
      if (num[i]) {
        return false;
      }
    }
    return true;
  }
};

class SolutionImpl {
  int sn;
  std::vector<Sticker> stickers, sum;
  int ans;
  void solve(int n, const Sticker & t, int s) {
    if (ans > 0 && s >= ans) {
      return;
    }
    if (t) {
      if (ans == -1 || ans > s) {
        ans = s;
      }
      return;
    }
    if (n == sn || !sum[n].feasible(t)) {
      return;
    }
    Sticker nt = t;
    for (int i = 1; ; ++i) {
      int j = 0;
      for (; j < 26; ++j) {
        if (nt.num[j] && stickers[n].num[j]) {
          break;
        }
      }
      if (j == 26) {
        break;
      }
      for (; j < 26; ++j) {
        nt.num[j] = std::max(0, nt.num[j] - stickers[n].num[j]);
      }
      solve(n + 1, nt, s + i);
    }
    solve(n + 1, t, s);
  }
public:
  SolutionImpl(const std::vector<std::string> & stickers_) : sn(stickers_.size()) {
    stickers.reserve(sn);
    for (const auto & st : stickers_) {
      stickers.emplace_back(st);
    }
    sum.resize(sn);
    Sticker s("");
    for (int i = sn - 1; i >= 0; --i) {
      for (int j = 0; j < 26; ++j) {
        s.num[j] += stickers[i].num[j];
      }
      sum[i] = s;
    }
  }
  int solve(const std::string & target) {
    ans = -1;
    solve(0, target, 0);
    return ans;
  }
};

class Solution {
public:
  int minStickers(const std::vector<std::string> &stickers,
                  const std::string &target) {
    return SolutionImpl(stickers).solve(target);
  }
};
