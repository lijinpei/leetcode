#include <iostream>
#include <cassert>
#include <string>
#include <cstdint>
#include <vector>
#include <unordered_set>

struct trie_node {
  char c;
  int id;
  trie_node *child, *sibling;
};

struct stack_node {
  int x, y, n;
  trie_node *p;

  stack_node() {}
  stack_node(int x, int y, int n, trie_node* p) : x(x), y(y), n(n), p(p) {}
};


trie_node *find(trie_node &r, char c) {
  for (trie_node *p = r.child; p; p = p->sibling) {
    char c1 = p->c;
    if (c == c1) {
      return p;
    } else if (c < c1) {
      return nullptr;
    }
  }
  return nullptr;
}

trie_node *insert(trie_node &r, char c) {
  if (!r.child || r.child->c > c) {
    return r.child = new trie_node{c, -1, nullptr, r.child};
  }
  trie_node *p = r.child;
  char c1 = p->c;
  while (true) {
    if (c1 == c) {
      return p;
    }
    trie_node *p1 = p->sibling;
    if (!p1) {
      return p->sibling = new trie_node{c, -1, nullptr, nullptr};
    }
    c1 = p1->c;
    if (c1 > c) {
      return p->sibling =
                 new trie_node{c, -1, nullptr, p->sibling};
    }
    p = p1;
  }
  assert(false);
  return nullptr;
}

bool add_to_trie(trie_node &root, const std::string &str, int &id) {
  trie_node *p = &root;
  for (auto c : str) {
    p = insert(*p, c);
  }
  if (p->id < 0) {
    p->id = id++;
    return true;
  } else {
    return false;
  }
}

class Solution {
public:
  std::vector<std::string> findWords(std::vector<std::vector<char>> &board_,
                                     std::vector<std::string> &words) {
    const uint8_t M1 = uint8_t(1) << 7;
    const uint8_t M2 = M1 - 1;
    int n = board_.size();
    int s = words.size();
    if (!n || !s) {
      return {};
    }
    int m = board_[0].size();
    if (!m) {
      return {};
    }
    std::vector<std::vector<uint8_t>> board(n + 2, std::vector<uint8_t>(m + 2));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        board[i + 1][j + 1] = board_[i][j];
      }
    }
    int ml = 0;
    int id = 0;
    std::vector<const std::string *> ids(s);
    trie_node root{' ', -1, nullptr, nullptr};
    for (const auto & str : words) {
      int l = str.size();
      if (l > ml) {
        ml = l;
      }
      if (add_to_trie(root, str, id)) {
        ids[id - 1] = &str;
      }
    }
    std::vector<bool> found(id, false);
    std::vector<stack_node> stack;
    stack.reserve(ml);
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        char c = board[i][j];
        trie_node* p = find(root, c);
        if (!p) {
          continue;
        }
        board[i][j] |= M1;
        stack.emplace_back(i, j, 0, p);
        while (!stack.empty()) {
          int x = stack.back().x, y = stack.back().y, n = stack.back().n++;
          trie_node* p = stack.back().p;
          if (p->id >= 0) {
            found[p->id] = true;
          }
          int x1, y1;
          switch (n) {
          case 0:
            x1 = x + 1;
            y1 = y;
            break;
          case 1:
            x1 = x - 1;
            y1 = y;
            break;
          case 2:
            x1 = x;
            y1 = y + 1;
            break;
          case 3:
            x1 = x;
            y1 = y - 1;
            break;
          default:
            board[x][y] &= M2;
            stack.pop_back();
            continue;
          }
          char c1 = board[x1][y1];
          trie_node* p1 = find(*p, c1);
          if (p1) {
            board[x1][y1] |= M1;
            stack.emplace_back(x1, y1, 0, p1);
          }
        }
      }
    }
    std::vector<std::string> ret;
    ret.reserve(id);
    for (int i = 0, s = found.size(); i < s; ++i) {
      if (found[i]) {
        ret.emplace_back(std::move(*ids[i]));
      }
    }
    return ret;
  }
};

int main() {
  Solution sol;
  std::vector<std::vector<char>>
      board{{ 'o', 'a', 'a', 'n' }, { 'e', 't', 'a', 'e' },
            { 'i', 'h', 'k', 'r' }, { 'i', 'f', 'l', 'v' }};
  std::vector<std::string> words{"oath","pea","eat","rain"};
  auto ret = sol.findWords(board, words);
  for (const auto v : ret) {
    std::cout << v << std::endl;
  }
}
