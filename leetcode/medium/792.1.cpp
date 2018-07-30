#include <iostream>
#include <vector>
#include <string>

class Solution {
  struct TrieNode {
    TrieNode *child, *sibling, *fail, *output;
    char c;
    int is_end;
    TrieNode(char c, TrieNode *child = nullptr, TrieNode *sibling = nullptr)
        : child(child), sibling(sibling), fail(nullptr), output(nullptr), c(c), is_end(-1) {
    }
    void dump() {
      std::cout << this << ':' << c << ':' << is_end << ':' << child << ':' << sibling << ':' << fail << ':' << output;
    }
  };

  template <bool canInsert = false>
    TrieNode* find(TrieNode* p, char c, int &count) {
      if (!p->child || c < p->child->c) {
        if (canInsert) {
          ++count;
          return p->child = new TrieNode(c, nullptr, p->child);
        } else {
          return nullptr;
        }
      }
      if (c == p->child->c) {
        return p->child;
      }
      p = p->child;
      while (true) {
        TrieNode* sib = p->sibling;
        if (!sib|| c < sib->c) {
          if  (canInsert) {
            ++count;
            return p->sibling = new TrieNode(c, nullptr, sib);
          } else {
            return nullptr;
          }
        }
        if (c == sib->c) {
          return sib;
        }
        p = sib;
      }
    }
  TrieNode* findOrInsert(TrieNode* p, char c, int & count) {
    return find<true>(p, c, count);
  }

  void addToTrie(TrieNode *root, const std::string & str, int & count, int n) {
    for (char c : str) {
      root = findOrInsert(root, c, count);
    }
    root->is_end = n;
  }

  void buildACTree(TrieNode* root, int trie_node_count) {
    int dump_count;
    std::vector<TrieNode*> queue(trie_node_count);
    int head = 0, tail = 0;
    auto popupate_child = [&](TrieNode *p) {
      TrieNode* p_fail = p->fail;
      for (TrieNode* ch = p->child; ch; ch = ch->sibling) {
        ch->fail = p_fail;
        queue[tail++] = ch;
      }
    };
    popupate_child(root);
    while (head < tail) {
      TrieNode* p = queue[head++];
      TrieNode* fail = p->fail;
      char c = p->c;
      while (fail) {
        TrieNode* next = find(fail, c, dump_count);
        if (next) {
          fail = next;
          break;
        } else {
          fail = fail->fail;
        }
      }
      if (fail) {
        p->fail = fail;
      } else {
        p->fail = root;
      }
      while (fail) {
        if (fail->is_end >= 0) {
          p->output = fail;
        }
        fail = fail->fail;
      }
      popupate_child(p);
    }
  }

  TrieNode* match(TrieNode* p, char c) {
    int dump_count;
    while (true) {
      TrieNode *p1 = find(p, c, dump_count);
      if (p1) {
        return p1;
      } else if (p->fail) {
        p = p->fail;
      } else {
        return p;
      }
    }
  }
  void dump(TrieNode *p, int indent = 0) {
    for (int i = 0; i < indent; ++i) {
      std::cout << ' ';
    }
    p->dump();
    std::cout << std::endl;
    for (TrieNode* ch = p->child; ch; ch = ch->sibling) {
      dump(ch, indent + 1);
    }
  }
public:
  int numMatchingSubseq(const std::string & str, std::vector<std::string> &words) {
    TrieNode root(' ');
    int trie_node_count = 0;
    int n = 0;
    for (const auto & word : words) {
      addToTrie(&root, word, trie_node_count, n++);
    }
    buildACTree(&root, trie_node_count);
    dump(&root);
    std::vector<bool> count(n);
    TrieNode* p = &root;
    for (char c : str) {
      p = match(p, c);
      if (p->is_end >= 0) {
        count[p->is_end] = true;
      }
      for (TrieNode* o = p->output; o; o= o->output) {
        count[o->is_end] = true;
      }
    }
    int ans = 0;
    for (auto b : count) {
      if (b) {
        ++ans;
      }
    }
    return ans;
  }
};

int main() {
  Solution sol;
  std::vector<std::string> words{std::string("a"),std::string("bb"),std::string("acd"),std::string("ace")};
  auto ret = sol.numMatchingSubseq("abcde", words);
  std::cout << ret << std::endl;
}
