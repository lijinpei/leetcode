#include <vector>
#include <string>
#include <iostream>
#include <stack>

template <class VT>
class trie_node {
public:
  trie_node *child, *sibling;
  VT val;
  char c;
  trie_node() : child(nullptr), sibling(nullptr), val() {}
  void output(std::vector<char> & s) {
    s.push_back(c);
    if (child) {
      child->output(s);
    } else {
      for (auto c : s) {
        std::cout << c;
      }
      std::cout << std::endl;
    }
    s.pop_back();
    for (trie_node * sb = sibling; sb; sb = sb->sibling) {
      sb->output(s);
    }
  }
};

template <class VT>
class simple_allocator {
  std::vector<VT> pool;
  size_t p;
public:
  simple_allocator() : simple_allocator(0) {}
  simple_allocator(size_t s) : pool(s), p(0) {}
  void reset(size_t s) {
    pool.resize(s);
    p = 0;
  }
  VT* allocate() {
    /*
    if (p == pool.size()) {
      abort();
    }
    */
    return &pool[p++];
  }
};

class WordFilter {
private:
  using SubTrieNodeT = trie_node<int>;
  using TrieNodeT = trie_node<SubTrieNodeT>;
  simple_allocator<SubTrieNodeT> sub_allocator;
  simple_allocator<TrieNodeT> allocator;
  TrieNodeT root;
  SubTrieNodeT prefix_root, suffix_root;
  simple_allocator<SubTrieNodeT> prefix_allocator, suffix_allocator;
  int s_max;

  template <class VT>
  static trie_node<VT>* insertChild(trie_node<VT>* p, char c, simple_allocator<trie_node<VT>>& alloc) {
    using TN = trie_node<VT>;
    auto newNode = [&](TN* &sibling) {
      TN *nc = alloc.allocate();
      nc->child = nullptr;
      nc->sibling = sibling;
      nc->c = c;
      sibling = nc;
      return nc;
    };
    if (!p->child || c < p->child->c) {
      return newNode(p->child);
    }
    TN *pc = p->child;
    if (c == pc->c ) {
      return pc;
    }
    for (TN *ch = pc->sibling; ch; pc = ch, ch = pc->sibling) {
      if (ch->c == c) {
        return ch;
      }
      if (ch->c > c) {
        return newNode(pc->sibling);
      }
    }
    return newNode(pc->sibling);
  }

  template <class VT, class CB, bool Inverse = false>
  static void addToTrieWithCallBack(const std::string & str, trie_node<VT> & root, CB & call_back, simple_allocator<trie_node<VT>> & alloc) {
    trie_node<VT> *p = &root;
    if (!Inverse) {
      for (int s = 0, s1 = str.size(); s < s1; ++s) {
        p = insertChild(p, str[s], alloc);
        call_back(str, *p);
      }
    } else {
      for (int s = str.size() - 1; s >= 0; --s) {
        p = insertChild(p, str[s], alloc);
        call_back(str, *p);
      }
    }
  }

  void addToTrie(const std::string & str, size_t i) {
    auto sub_callback = [i](const std::string &, SubTrieNodeT& n) {
      n.val = i;
    };
    auto callback = [&](const std::string & str, TrieNodeT& n) {
      addToTrieWithCallBack<int, decltype(sub_callback), true>(str, n.val, sub_callback, sub_allocator);
    };
    addToTrieWithCallBack(str, prefix_root, sub_callback, prefix_allocator);
    addToTrieWithCallBack<int, decltype(sub_callback), true>(str, suffix_root, sub_callback, suffix_allocator);
    addToTrieWithCallBack(str, root, callback, allocator);
  }

  template <class VT, bool Inverse = false>
  static const trie_node<VT>* find(const std::string & str, const trie_node<VT>& root) {
    const trie_node<VT> * p = &root;
    auto find_child = [](const trie_node<VT>* p, char c) -> trie_node<VT>* {
      trie_node<VT>* ch = p->child;
      while(ch) {
        if (ch->c >= c) {
          break;
        }
        ch = ch->sibling;
      }
      return (ch && ch->c == c ? ch : nullptr);
    };

    if (!Inverse) {
      for (int s = 0, s1 = str.size(); s < s1; ++s) {
        p = find_child(p, str[s]);
        if (!p) {
          return nullptr;
        }
      }
    } else {
      for (int s = str.size() - 1; s >= 0; --s) {
        p = find_child(p, str[s]);
        if (!p) {
          return nullptr;
        }
      }
    }
    return p;
  }

public:
    WordFilter(const std::vector<std::string> & words) {
      root = TrieNodeT();
      prefix_root = SubTrieNodeT();
      suffix_root = SubTrieNodeT();
      size_t l1 = 0, l2 = 0;
      s_max = words.size() - 1;
      for (const auto & str : words) {
        l1 += str.size();
        l2 += str.size() * str.size();
      }
      prefix_allocator.reset(l1);
      suffix_allocator.reset(l1);
      allocator.reset(l1);
      sub_allocator.reset(l2);
      for (size_t i = 0, e = words.size(); i < e; ++i) {
        addToTrie(words[i], i);
      }
    }

    int f(std::string prefix, std::string suffix) {
      int s1 = prefix.size(), s2 = suffix.size();
      if (!s1 && !s2) {
        return s_max;
      }
      if (!s1) {
        const SubTrieNodeT* p = find<int, true>(suffix, suffix_root);
        /*
        std::vector<char> st;
        suffix_root.output(st);
        */
        return p ? p->val : -1;
      }
      if (!s2) {
        const SubTrieNodeT* p = find(prefix, prefix_root);
        return p ? p->val : -1;
      }
      const TrieNodeT* root1 = find(prefix, root);
      if (!root1) {
        return -1;
      }
      const SubTrieNodeT* root2 = find<int, true>(suffix, root1->val);
      return root2 ? root2->val : -1;
    }
};

int main() {
  /*
  WordFilter wf({"abbbababbb","baaabbabbb","abababbaaa","abbbbbbbba","bbbaabbbaa","ababbaabaa","baaaaabbbb","babbabbabb","ababaababb","bbabbababa"});
  std::cout << wf.f("", "abaa") << std::endl;
  std::cout << wf.f("babbab", "") << std::endl;
  */
  WordFilter wf({"WordFilter", "f"});
}

