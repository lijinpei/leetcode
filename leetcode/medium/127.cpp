#include <iostream>
#include <string>
#include <vector>
#include <cassert>

struct trie_node {
  char c;
  trie_node *sibling = nullptr;
  union {
    trie_node *child = nullptr;
    int id;
  };
};

trie_node *find_child(trie_node &r, char c) {
  if (!r.child) {
    return nullptr;
  }
  auto *p = r.child;
  if (p->c > c) {
    return nullptr;
  }
  while (true) {
    if (p->c == c) {
      return p;
    } else if (!p->sibling || p->sibling->c > c) {
      return nullptr;
    } else {
      p = p->sibling;
    }
  }
  assert(false);
  return nullptr;
}

trie_node *insert_child(trie_node &r, char c) {
  if (!r.child) {
    r.child = new trie_node{c, nullptr, nullptr};
    return r.child;
  }
  auto *p = r.child;
  if (p->c > c) {
    r.child = new trie_node{c, r.child, nullptr};
    return r.child;
  }
  while (true) {
    if (p->c == c) {
      return p;
    } else if (!p->sibling) {
      p->sibling = new trie_node{c, nullptr, nullptr};
      return p->sibling;
    } else if (p->sibling->c > c) {
      p->sibling = new trie_node{c, p->sibling, nullptr};
      return p->sibling;
    } else {
      p = p->sibling;
    }
  }
  assert(false);
  return nullptr;
}
int add_to_trie(trie_node &root, const std::string &str, int id) {
  auto *p = &root;
  for (auto c : str) {
    p = insert_child(*p, c);
  }
  if (!p->id) {
    p->id = id;
  }
  return p->id;
}

class Solution {
  class Impl {
    std::string const &beginWord;
    std::string const &endWord;
    std::vector<std::string> const &wordList;
    int l, s;
    std::vector<int> dis;
    trie_node trie_root;
    std::vector<int> bfs_queue;
    int head, tail;
    bool stop;
    void bfs1(const std::string &str, int d, int i, trie_node *p) {
      ++i;
      for (int j = str.size(); i < j; ++i) {
        p = find_child(*p, str[i]);
        if (!p) {
          return;
        }
      }
      int &d1 = dis[p->id];
      if (!d1 && p->id != s + 1) {
        d1 = d + 1;
        if (p->id == s) {
          stop  = true;
        } else {
          bfs_queue[tail++] = p->id;
        }
      }
    }
    void bfs() {
      // distance of beginWord
      dis[s + 1] = 1;
      head = -1;
      tail = 0;
      bfs_queue[0] = s + 1;
      const std::string *st = &beginWord;
      int d = 1;
      do {
        // expand (s, d)
        trie_node *p = &trie_root;
        for (int i = 0, j = st->size(); i < j; ++i) {
          trie_node *np = nullptr;
          for (trie_node *ch = p->child; ch; ch = ch->sibling) {
            if (ch->c == (*st)[i]) {
              np = ch;
            } else {
              bfs1(*st, d, i, ch);
              if (stop) {
                return;
              }
            }
          }
          if (!np) {
            break;
          }
          p = np;
        }
        ++head;
        st = &wordList[bfs_queue[head]];
        d = dis[bfs_queue[head]];
      } while (head <= tail);
    }

  public:
    Impl(std::string const &beginWord, std::string const &endWord,
         std::vector<std::string> const &wordList)
        : beginWord(beginWord), endWord(endWord), wordList(wordList),
          l(beginWord.size()), s(wordList.size()), dis(s + 2),
          bfs_queue(s), stop(false) {}
    int solve() {
      if (l != int(endWord.size())) {
        return 0;
      }
      if (beginWord == endWord) {
        return 0;
      }
      add_to_trie(trie_root, beginWord, s + 1);
      add_to_trie(trie_root, endWord, s);
      bool ok = false;
      for (int i = 0, j = wordList.size(); i < j; ++i) {
        if (l != int(wordList[i].size())) {
          continue;
        }
        if (add_to_trie(trie_root, wordList[i], i) == s) {
          ok = true;
        }
      }
      if (!ok) {
        return 0;
      }
      bfs();
      return dis[s];
    }
  };

public:
  int ladderLength(std::string const &beginWord, std::string const &endWord,
                   std::vector<std::string> const &wordList) {
    return Impl(beginWord, endWord, wordList).solve();
  }
};

int main() {
  Solution sol;
  std::vector<std::string> vec{"hot", "dot", "dog", "lot", "log", "cog"};
  auto ret = sol.ladderLength("hit", "cog", vec);
  std::cout << ret << std::endl;
}
