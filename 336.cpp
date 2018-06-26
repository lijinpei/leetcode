#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

struct TrieNode {
  TrieNode *child, *sibling;
  int num;
  char c;

  TrieNode(char c) : child(nullptr), sibling(nullptr), num(-1), c(c) {}
  TrieNode(char c, TrieNode *child, TrieNode *sibling)
      : child(child), sibling(sibling), num(-1), c(c) {}
  TrieNode() : TrieNode(' ') {}
};

void dumpTrie(TrieNode * root, std::string  str) {
  if (root->num >= 0) {
    std::cout << root->num << ": " << str << std::endl;
  }
  for (TrieNode* ch = root->child; ch; ch = ch->sibling) {
    str.push_back(ch->c);
    dumpTrie(ch, str);
    str.pop_back();
  }
}

TrieNode *findChild(TrieNode *root, char c) {
  if (!root->child) {
    return nullptr;
  }
  if (root->child->c > c) {
    return nullptr;
  }
  if (root->child->c == c) {
    return root->child;
  }
  for (TrieNode *ch = root->child; ch;) {
    TrieNode *ch1 = ch->sibling;
    if (!ch1) {
      return nullptr;
    }
    if (c < ch1->c) {
      return nullptr;
    }
    if (c == ch1->c) {
      return ch1;
    }
    ch = ch1;
  }
  return nullptr;
}

TrieNode *findOrInsert(TrieNode *root, char c) {
  if (!root->child) {
    return root->child = new TrieNode(c);
  }
  if (root->child->c > c) {
    return root->child = new TrieNode(c, nullptr, root->child);
  }
  if (root->child->c == c) {
    return root->child;
  }
  for (TrieNode *ch = root->child; ch;) {
    TrieNode *ch1 = ch->sibling;
    if (!ch1) {
      return ch->sibling = new TrieNode(c);
    }
    if (c < ch1->c) {
      return ch->sibling = new TrieNode(c, nullptr, ch->sibling);
    } else if (c == ch1->c) {
      return ch->sibling;
    } else {
      ch = ch1;
    }
  }
  return nullptr;
}

void addToTrie(TrieNode *root, int num, const std::string &word) {
  //TrieNode * old_root = root;
  //std::cout << "word.size() " << word.size() << std::endl;
  for (int s = word.size() - 1; s >= 0; --s) {
    root = findOrInsert(root, word[s]);
    //std::cout << root << ' ';
  }
  root->num = num;
  //std::cout << "dump trie\n";
  //dumpTrie(old_root, "");
}

template <typename CB> void recursiveVisitChild(TrieNode *root, CB &&cb) {
  for (TrieNode *ch = root->child; ch; ch = ch->sibling) {
    if (ch->num >= 0) {
      cb(ch->num);
    }
    recursiveVisitChild(ch, cb);
  }
}

void Manacher(const std::string &pattern, std::vector<bool> & head_parl, std::vector<bool> & tail_parl) {
  int s = pattern.size();
  if (!s) {
    return;
  }
  head_parl.resize(s);
  tail_parl.resize(s);
  std::vector<int> len_odd(s);
  std::vector<int> len_even(s);
  int mv_odd = 1, mp_odd = 0;
  int mv_even = 0, mp_even = 0;
  len_odd[0] = 1;
  len_even[0] = mv_even;
  head_parl[0] = true;
  if (s == 1) {
    tail_parl[0] = true;
  }
  auto odd_contains = [&](int p) {
    return mv_even + mp_even > p;
  };
  auto even_contains = [&](int p) {
    return mv_even + mp_even > p;
  };
  auto odd_par = [&](int p) {
    return 2 * mp_odd - p;
  };
  auto even_par = [&](int p) {
    //std::cout << "mp_even " << mp_even << std::endl;
    return 2 * mp_even - p - 1;
  };
  auto odd_start = [&](int p) {
    return p - len_odd[p] + 1;
  };
  auto even_start = [&](int p) {
    return p - len_even[p];
  };
  auto grow_odd = [&](int p, int st) {
    for (; p - st >= 0 && p + st < s && pattern[p - st] == pattern[p + st]; ++st) {
    }
    if (p + st > s) {
      st = s - p;
    }
    if (p + st > mp_odd + mv_odd) {
      mp_odd = p;
      mv_odd = st;
    }
    len_odd[p] = st;
  };
  auto grow_even = [&](int p, int st) {
    //std::cout << "grow_even " << p << ' ' << st << std::endl;
    for (; p - st - 1 >= 0 && p + st < s && pattern[p - st - 1] == pattern[p + st]; ++st) {
    }
    if (p + st > s) {
      st = s - p;
    }
    if (p + st > mp_even + mv_even) {
      mp_even = p;
      mv_even = st;
    }
    len_even[p] = st;
  };
  auto expand_par = [&](int p, int par, int start) {
    //std::cout << "p " << p << " par " << par << std::endl;
    if (odd_start(par) != start) {
      len_odd[p] = std::min(len_odd[par], par - start + 1);
    } else {
      //std::cout << "grow_odd\n";
      grow_odd(p, std::min(len_odd[par], par - start + 1));
    }
    int par1 = par + 1;
    //std::cout << "par1 " << par1 << std::endl;
    if (even_start(par1) != start) {
      len_even[p] = std::min(len_even[par1], par1 - start);
    } else {
      //std::cout << "grow_even\n";
      grow_even(p, std::min(len_even[par1], par1 - start));
    }
  };
  auto expand = [&](int p) {
    grow_odd(p, 1);
    grow_even(p, 0);
  };
  for (int i = 1; i < s; ++i) {
    //std::cout << i << ' ';
    if (even_contains(i)) {
      //std::cout << "even_contains\n";
      expand_par(i, even_par(i), even_start(mp_even));
    } else if (odd_contains(i)) {
      //std::cout << "odd_contains\n";
      expand_par(i, odd_par(i), odd_start(mp_odd));
    } else {
      //std::cout << "else\n";
      expand(i);
    }
    if (i + len_even[i] == s) {
      tail_parl[i - len_even[i]] = true;
    }
    if (i + len_odd[i] == s) {
      tail_parl[i - len_odd[i] + 1] = true;
    }
    if (i - len_even[i] == 0) {
      head_parl[i + len_even[i] - 1] = true;
    }
    if (i - len_odd[i] + 1 == 0) {
      head_parl[i + len_odd[i] - 1] = true;
    }
  }
  //for (auto b : len_even) {
    //std::cout << b << ' ';
  //}
  //std::cout << std::endl;
  //for (auto b : len_odd) {
    //std::cout << b << ' ';
  //}
  //std::cout << std::endl;
}

class Solution {
public:
  std::vector<std::vector<int>>
  palindromePairs(std::vector<std::string> &words) {
    int n = words.size();
    TrieNode root;
    for (int i = 0; i < n; ++i) {
      //std::cout << "add: " << i << std::endl;
      addToTrie(&root, i, words[i]);
    }
    //dumpTrie(&root, "");
    std::vector<std::vector<bool>> head_palindrome_pos(n),
        tail_palindrome_pos(n);
    for (int i = 0; i < n; ++i) {
      const auto &word = words[i];
      Manacher(word, head_palindrome_pos[i], tail_palindrome_pos[i]);
      //if (i != 15) {
        //continue;
      //}
      //std::cout << "head_palindrome_pos " << head_palindrome_pos[i].size() << std::endl;
      //for (auto h : head_palindrome_pos[i]) {
        //std::cout << h << ' ';
      //}
      //std::cout << std::endl;
      //std::cout << "tail_palindrome_pos " << tail_palindrome_pos[i].size() << std::endl;
      //for (auto t : tail_palindrome_pos[i]) {
        //std::cout << t << ' ';
      //}
      //std::cout << std::endl;
    }
    std::vector<std::vector<int>> ret;
    std::vector<int> ret1;
    for (int i = 0; i < n; ++i) {
      if (root.num == i) {
        //std::cout << "start rec child " << i << std::endl;
        for (int j = 0; j < n; ++j) {
          if (i == j) {
            continue;
          }
          if (tail_palindrome_pos[j][0]) {
            ret1 = {i, j};
            ret.emplace_back(std::move(ret1));
            ret1 = {j, i};
            ret.emplace_back(std::move(ret1));
          }
        }
        continue;
      }
      const auto &word = words[i];
      int s = word.size();
      const auto &tail_pal = tail_palindrome_pos[i];
      TrieNode *p = &root;
      for (int j = 0; j < s; ++j) {
        p = findChild(p, word[j]);
        if (!p) {
          //std::cout << "break " << i << ' ' << j << ' ' << word[j] << std::endl;
          //dumpTrie(&root, "");
          break;
        }
        if (p->num >= 0) {
          //std::cout << "visit1: " << i << ' ' << j << ' ' << p->num << std::endl;
          if (p->num != i && (j == s - 1 || tail_pal[j + 1])) {
          ret1 = {i, p->num};
          ret.emplace_back(std::move(ret1));
          }
        }
      }
      if (!p) {
        continue;
      }
      //std::cout << "start rec child " << i << std::endl;
      recursiveVisitChild(p, [&](int n) {
        //std::cout << "rec child " << i << ' ' << n << std::endl;
        int s1 = words[n].size();
        int d = s1 - s;
        const auto &head_pal = head_palindrome_pos[n];
        if (head_pal[d - 1]) {
          ret1 = {i, n};
          ret.emplace_back(std::move(ret1));
        }
      });
    }
    return ret;
  }
};

int main() {
  Solution sol;
  std::string input1[] = {"bbbbbabbabbbb"};
  //std::string input1[] = {"abcd","dcba","lls","s","sssll"};
  //std::string input1[] = {"lls"};
  std::vector<std::string> input2;
  for (auto p : input1) {
    input2.emplace_back(p);
  }
  auto ret = sol.palindromePairs(input2);
  for (const auto & r : ret) {
    std::cout << r[0] << ' ' << r[1] << std::endl;
  }
}
