#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

class Solution {
  struct TrieNode {
    TrieNode *child, *father, *sibling, *fail;
    int depth;
    bool is_end;
    char c;
    TrieNode(char c, int depth, TrieNode *child = nullptr, TrieNode *sibling = nullptr)
        : child(child), sibling(sibling), fail(nullptr), depth(depth), is_end(false), c(c)  {}
    void dump() {
      std::cout << c << ':' << this << ':' << child << ':' << sibling << ':' << fail << ':' << depth;
    }
  };
  TrieNode root;
  int node_count;
  template <bool canInsert>
  TrieNode* find(TrieNode* root, char c) {
    int depth = root->depth + 1;
    if (!root->child || c < root->child->c) {
      if (canInsert) {
        ++node_count;
        return root->child = new TrieNode(c, depth, nullptr, root->child);
      } else {
        return nullptr;
      }
    }
    if (c == root->child->c) {
      return root->child;
    }
    for (TrieNode* ch = root->child; ch;) {
      TrieNode * ch1 = ch->sibling;
      if (!ch1 || ch1->c > c) {
        if (canInsert) {
          ++node_count;
          return ch->sibling = new TrieNode(c, depth, nullptr, ch1);
        } else {
          return nullptr;
        }
      }
      if (ch1->c == c) {
        return ch1;
      }
      ch = ch1;
    }
    abort();
  }
  TrieNode* findOrInsert(TrieNode* root, char c) {
    return find<true>(root, c);
  }
  TrieNode* find(TrieNode* root, char c) {
    return find<false>(root, c);
  }
  void addToTrie(const std::string & str) {
    TrieNode *p= &root;
    for (char c : str) {
      p = findOrInsert(p, c);
    }
    p->is_end = true;
  }
  void buildACTree() {
    std::vector<TrieNode*> queue(node_count);
    int head = 0, tail = 0;
    auto populate_child = [&](TrieNode* p) {
      TrieNode* p_fail = p->fail;
      for (TrieNode* ch = p->child; ch; ch = ch->sibling) {
        ch->fail = p_fail;
        queue[tail++] = ch;
      }
    };
    root.fail = nullptr;
    populate_child(&root);
    while (head < tail) {
      TrieNode *p = queue[head++];
      char c = p->c;
      TrieNode* fa_fail = p->fail, *next = nullptr;
      if (!fa_fail) {
        p->fail = &root;
      } else {
        while (true) {
          next = find(fa_fail, c);
          if (next) {
            p->fail = next;
            break;
          } else {
            fa_fail = fa_fail->fail;
            if (!fa_fail) {
              p->fail = &root;
              break;
            }
          }
        }
      }
      populate_child(p);
    }
  }
  void dumpTrie(TrieNode* p, int indent = 0) {
    for (int i = 0; i < indent; ++i) {
      std::cout << ' ';
    }
    p->dump();
    std::cout << std::endl;
    for (TrieNode* ch = p->child; ch; ch = ch->sibling) {
      dumpTrie(ch, indent + 1);
    }
  }
public:
  Solution() : root(' ', 0), node_count(0) {}
  bool wordBreak(const std::string &str, const std::vector<std::string>& wordDict) {
    for (auto & word : wordDict) {
      addToTrie(word);
    }
    buildACTree();
    //dumpTrie(&root);
    int s = str.size();
    std::vector<bool> dp(s + 1);
    dp[0] = true;
    TrieNode* p = &root;
    for (int i = 0; i < s; ++i) {
      char c = str[i];
      while (true) {
        TrieNode* p1 = find(p, c);
        if (p1) {
          p = p1;
          break;
        } else {
          p1 = p->fail;
          if (p1) {
            p = p1;
          } else {
            break;
          }
        }
      }
      if (p->is_end && dp[i + 1 - p->depth]) {
        dp[i + 1] = true;
      }
      for (TrieNode* p1 = p->fail; p1; p1 = p1->fail) {
        if (p1->is_end && dp[i + 1 - p1->depth]) {
          dp[i + 1] = true;
        }
      }
    }
    if (dp[s]) {
      return true;
    }
    while (true) {
      p = p->fail;
      if (!p) {
        break;
      }
      if (p->is_end && dp[s - p->depth]) {
        return true;
      }
    }
    for (auto b : dp) {
      std::cout << b << ' ';
    }
    std::cout << std::endl;
    return false;
  }
};
