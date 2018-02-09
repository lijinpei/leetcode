#include <vector>
#include <string>
#include <iostream>

class Solution {
  std::vector<std::string> ret;
  int l, n, p, last_pos, ws;
  void addToRet(int p, const std::vector<std::string>& words, int maxWidth) {
    ret.emplace_back(maxWidth, ' ');
    int n_sp = maxWidth - l;
    int n_sp1, n_sp2;
    if (n != 1) {
      n_sp1 = n_sp / (n - 1);
      n_sp2 = n_sp % (n - 1);
    }
    int lp = 0;
    for (int i = last_pos; i < p; ++i) {
      int j = i - last_pos;
      //std::copy(ret.back().begin() + lp, ret.back().begin() + lp + words[i].size(), words[i].begin());
      //ret.back().substr(lp, words[i].size()) = words[i];
      ret.back().replace(lp, words[i].size(), words[i]);
      lp += words[i].size() + n_sp1;
      if (j < n_sp2) {
        lp += 1;
      }
    }
    last_pos = p;
    l = words[p].size();
    n = 1;
  }

  void addLast(const std::vector<std::string>& words, int maxWidth) {
    ret.emplace_back(maxWidth, ' ');
    int lp = 0;
    for (int i = last_pos; i < ws; ++i) {
      //std::copy(ret.back().begin() + lp, ret.back().begin() + lp + words[i].size(), words[i].begin());
      //ret.back().substr(lp, words[i].size()) = words[i];
      ret.back().replace(lp, words[i].size(), words[i]);
      lp += words[i].size() + 1;
    }
  }

public:
  std::vector<std::string> fullJustify(const std::vector<std::string>& words, int maxWidth) {
    ret = {};
    last_pos = 0;
    ws = words.size();
    l = 0;
    n = 0;
    for (p = 0; p < ws; ++p) {
      const std::string & w = words[p];
      int s = w.size();
      if (l + n + s <= maxWidth) {
        l += s;
        ++n;
      } else {
        addToRet(p, words, maxWidth);
      }
    }
    addLast(words, maxWidth);
    return ret;
  }
};

int main() {
  std::vector<std::string> words;
  words.push_back("This");// "is", "an", "example", "of", "text", "justification."};
  words.push_back("is");
  words.push_back("an");
  words.push_back("example");
  words.push_back("of");
  words.push_back("text");
  words.push_back("Justifaction");
  Solution sol;
  for (auto & r : words) {
    std::cout << r << std::endl;
  }
  auto ret = sol.fullJustify(words, 16);
  for (auto & r : ret) {
    std::cout << r << std::endl;
  }
}
