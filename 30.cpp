#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <list>

struct trie_node {
  char c;
  trie_node *child, *sibling, *failed;
  int id;
};

trie_node* addToTrie(trie_node & root, std::string & word) {
  trie_node* p = &root;
  for (auto c : word) {
    if (!p->child) {
      p->child = new trie_node{c, nullptr, nullptr, nullptr, -1};
      p = p->child;
      continue;
    }
    if (p->child->c > c) {
      trie_node* np = new trie_node{c, nullptr, p->child, nullptr, -1};
      p->child = np;
      p = np;
      continue;
    }
    trie_node* np = p->child;
    while (np->sibling && c >= np->sibling->c) {
      np = np->sibling;
    }
    if (c == np->c) {
      p = np;
      continue;
    }
    trie_node* np1 = new trie_node{c, nullptr, np->sibling, nullptr, -1};
    np->sibling = np1;
    p = np1;
  }
  return p;
}

trie_node* findChild(trie_node* p, char c) {
  for (trie_node* ch = p->child; ch; ch = ch->sibling) {
    if (c == ch->c) {
      return ch;
    }
    if (c < ch->c) {
      return nullptr;
    }
  }
  return nullptr;
}


/*
void buildFailed(trie_node & root) {
  std::list<std::pair<trie_node*, trie_node*>> st;
  root.failed = nullptr;
  for (trie_node* p = root.child; p; p = p->sibling) {
    st.emplace_back(&root, p);
  }
  auto buildFailed_impl = [&](trie_node* n, trie_node* p) {
    char c = n->c;
    trie_node* p1 = p->failed, *p2;
    while (p1) {
      p2 = findChild(p1, c);
      if (p2) {
        break;
      }
      p1 = p1->failed;
    }
    n->failed = p1 ? p2 : &root;
    for (trie_node* ch = n->child; ch; ch = ch->sibling) {
      st.emplace_back(n, ch);
    }
  };
  while (!st.empty()) {
    auto p = st.front();
    st.pop_front();
    buildFailed_impl(p.second, p.first);
  }
}
*/

void buildFailed_impl(trie_node* n, trie_node* p, trie_node* r) {
  if (n->failed) {
    return;
  }
  char c = n->c;
  trie_node* p1 = p->failed, *p2;
  while (p1) {
    p2 = findChild(p1, c);
    if (p2) {
      break;
    }
    p1 = p1->failed;
  }
  if (p1) {
    n->failed = p2;
    buildFailed_impl(p2, p1, r);
  } else {
    n->failed = r;
  }
  for (trie_node* ch = n->child; ch; ch = ch->sibling) {
    buildFailed_impl(ch, n, r);
  }
}

void buildFailed(trie_node & root) {
  root.failed = nullptr;
  for (trie_node* p = root.child; p; p = p->sibling) {
    buildFailed_impl(p, &root, &root);
  }
}

void findMatch(std::vector<int> &pos, std::string &str, trie_node& root) {
  trie_node* p = &root;
  for (int i = 0, s = str.size(); i < s; ++i) {
again:
    trie_node* p1 = findChild(p, str[i]);
    if (p1) {
      p = p1;
      if (!p->child) {
        pos[i] = p->id;
      }
      continue;
    }
    if (p->failed) {
      p = p->failed;
      goto again;
    } else {
      p = &root;
    }
  }
}

class Solution {
public:
  std::vector<int> findSubstring(std::string &str, std::vector<std::string> &words) {
    trie_node root{' ', nullptr, nullptr, nullptr, -1};
    int id = 0;
    int s1 = words.size();
    int s2 = words[0].size();
    std::vector<int> require(s1);
    for (auto & word : words) {
      trie_node* n = addToTrie(root, word);
      if (n->id == -1) {
        n->id = id++;
      }
      ++require[n->id];
    }
    buildFailed(root);
    int s = str.size();
    std::vector<int> pos(s, -1);
    findMatch(pos, str, root);
    std::vector<int> total(s2);
    std::vector<std::vector<int>> count(s2, std::vector<int>(id));
    std::vector<int> ret;
    if (s < s1 * s2) {
      return ret;
    }
    auto add = [&](int p, int i) -> bool {
      int v = pos[i];
      if (-1 == v) {
        return false;
      }
      ++count[p][v];
      if (count[p][v] == require[v]) {
        ++total[p];
      }
      return total[p] == id;
    };
    auto remove = [&](int p, int i) {
      int v = pos[i];
      if (-1 == v) {
        return;
      }
      --count[p][v];
      if (count[p][v] < require[v]) {
        --total[p];
      }
    };
    int s12 = s1 * s2;
    for (int i = 0, p = 0; i < s; ++i, p = (p + 1 == s2 ? 0 : p + 1)) {
      if (i >= s12) {
        remove(p, i - s12);
      }
      if (add(p, i)) {
        ret.push_back(i - s12 + 1);
      }
    }
    return ret;
  }
};

int main() {
  Solution sol;
  std::string input1;
  std::vector<std::string> input2;
  std::cin >> input1;
//  std::cerr << input1 << ' ' << input1.size() << std::endl;
  for (int i = 0; i < 208; ++i) {
    std::string tmp;
    std::cin >> tmp;
    input2.push_back(tmp);
//    std::cerr << tmp << ' ' << tmp.size() << std::endl;
  }
  auto ret = sol.findSubstring(input1, input2);
  for (auto p : ret) {
    std::cerr << p << ' ';
  }
  std::cerr << std::endl;
}
