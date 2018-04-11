#include <cassert>
#include <forward_list>
#include <iostream>
#include <numeric>
#include <stack>
#include <string>
#include <vector>

struct trie_node {
  char c;
  bool is_leaf;
  trie_node *child, *sibling, *fail;
  int l;
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

trie_node *insert(trie_node &r, char c, int &nc, int l) {
  if (!r.child || r.child->c > c) {
    ++nc;
    return r.child = new trie_node{c, false, nullptr, r.child, nullptr, l};
  }
  trie_node *p = r.child;
  char c1 = p->c;
  while (true) {
    if (c1 == c) {
      return p;
    }
    trie_node *p1 = p->sibling;
    if (!p1) {
      ++nc;
      return p->sibling = new trie_node{c, false, nullptr, nullptr, nullptr, l};
    }
    c1 = p1->c;
    if (c1 > c) {
      ++nc;
      return p->sibling =
                 new trie_node{c, false, nullptr, p->sibling, nullptr, l};
    }
    p = p1;
  }
  assert(false);
  return nullptr;
}

int add_to_trie(trie_node &root, const std::string &str) {
  trie_node *p = &root;
  int ret = 0;
  int l = 1;
  for (auto c : str) {
    p = insert(*p, c, ret, l++);
  }
  p->is_leaf = true;
  return ret;
}

void build_ac_tree(trie_node &root, int nc) {
  std::vector<std::pair<trie_node *, trie_node *>> queue(nc);
  int head = 0, tail = 0;
  for (trie_node *p = root.child; p; p = p->sibling) {
    p->fail = &root;
    // std::cout << p->c << ' ';
    for (trie_node *ch = p->child; ch; ch = ch->sibling) {
      queue[tail++] = {&root, ch};
    }
  }
  // std::cout << std::endl;
  while (head < tail) {
    trie_node *p = queue[head].first;
    trie_node *ch = queue[head].second;
    ++head;
    char c = ch->c;
    do {
      trie_node *p1 = find(*p, c);
      if (p1) {
        p = p1;
        break;
      } else {
        p = p->fail;
      }
    } while (p);
    ch->fail = p = p ? p : &root;
    // std::cout << ch->c << ' ' << ch->l << ' ' << p->c << ' ' << p->l <<
    // std::endl;
    for (trie_node *ch1 = ch->child; ch1; ch1 = ch1->sibling) {
      queue[tail++] = {p, ch1};
    }
  }
}

class Solution {
public:
  std::vector<std::string> wordBreak(const std::string &str,
                                     const std::vector<std::string> &wordDict) {
    int s = str.size();
    if (!s) {
      return {};
    }
    if (!wordDict.size()) {
      return {};
    }
    trie_node root{' ', false, nullptr, nullptr, nullptr, 0};
    int nc = 0;
    for (const auto &str : wordDict) {
      nc += add_to_trie(root, str);
    }
    build_ac_tree(root, nc);
    trie_node *p = &root;
    std::vector<std::forward_list<int>> child(s);
    for (int i = 0; i < s; ++i) {
      char c = str[i];
      do {
        trie_node *p1 = find(*p, c);
        if (p1) {
          p = p1;
          break;
        } else {
          p = p->fail;
        }
      } while (p);
      for (trie_node *p1 = p; p1; p1 = p1->fail) {
        if (p1->is_leaf) {
          int start = i - p1->l + 1;
          // std::cout << "match1 " << start << ' ' << i + 1 << std::endl;
          child[start].push_front(i + 1);
        }
      }
      if (!p) {
        p = &root;
      }
    }
    /*
    for (auto v : fa) {
      std::cout << v << ' ';
    }
    std::cout << std::endl;
    */
    std::vector<int> num(s + 1, 0);
    num[s] = 1;
    for (int i = s - 1; i >= 0; --i) {
      int n = 0;
      for (auto c : child[i]) {
        n += num[c];
      }
      num[i] = n;
    }
    if (!num[0]) {
      return {};
    }
    std::vector<std::string> ret(num[0]);
    int n = 0;
    std::vector<std::pair<int, std::forward_list<int>::iterator>> st;
    st.emplace_back(0, child[0].begin());
    while (!st.empty()) {
      int c = st.back().first;
      auto itor = st.back().second;
      if (itor == child[c].end()) {
        st.pop_back();
        continue;
      }
      int ch = *itor;
      st.back().second = ++itor;
      if (ch == s) {
        std::string ret_str;
        ret_str.reserve(s + st.size() - 1);
        int lp = 0;
        for (int i = 1, ss = st.size(); i < ss; ++i) {
          int v = st[i].first;
          ret_str += str.substr(lp, v - lp);
          ret_str += " ";
          lp = v;
        }
        ret_str += str.substr(lp, s);
        ret[n++] = std::move(ret_str);
      } else {
        st.emplace_back(ch, child[ch].begin());
      }
    }
    return ret;
  }
};

int main() {
  std::string str("abcd");
  std::vector<std::string> word_dict{"a", "abc", "b", "cd"};
  Solution sol;
  auto ret = sol.wordBreak(str, word_dict);
  for (auto &v : ret) {
    std::cout << v << ',';
  }
  std::cout << std::endl;
}
