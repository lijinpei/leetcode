#include <iostream>
#include <vector>
#include <string>

class Solution {
  struct TrieNode {
    TrieNode *child, *sibling;
    int weight, p;
    char c;
    TrieNode(char c, TrieNode *child = nullptr, TrieNode *sibling = nullptr)
        : child(child), sibling(sibling), weight(0), p(0), c(c) {}
    void dump() {
      std::cout << c << ':' << weight << ':' << p;
    }
  };
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
    int s = str.size();
    int ans = 0;
    int node_count = 0;
    TrieNode root(' ');
    auto findOrInsert = [&node_count](TrieNode* p, char c) -> TrieNode* {
      if (!p->child || p->child->c > c) {
        ++node_count;
        return p->child = new TrieNode(c, nullptr, p->child);
      }
      if (p->child->c == c) {
        return p->child;
      }
      for (TrieNode *ch = p->child;;) {
        TrieNode *ch1 = ch->sibling;
        if (!ch1 || ch1->c > c) {
          ++node_count;
          return ch->sibling = new TrieNode(c, nullptr, ch1);
        }
        if (c == ch1->c) {
          return ch1;
        }
        ch = ch1;
      }
    };
    for (const auto & word : words) {
      TrieNode* p = &root;
      for (char c : word) {
        p = findOrInsert(p, c);
      }
      ++p->weight;
    }
    root.p = 0;
    std::vector<TrieNode*> queue(node_count + 1);
    int head = 0, tail = 1;
    queue[0] = &root;
    int flag[26] = {};
    int pos[26] = {};
    int n = 0;
    while (head < tail) {
      TrieNode * p = queue[head++];
      ++n;
      int p1 = p->p;
      for (TrieNode * ch = p->child; ch; ch = ch->sibling) {
        int c = ch->c - 'a';
        if (flag[c] == n) {
          ch->p = pos[c];
          queue[tail++] = ch;
          ans += ch->weight;
          continue;
        }
        while (p1 < s) {
          int c1 = str[p1++] - 'a';
          if (flag[c1] != n) {
            flag[c1] = n;
            pos[c1] = p1;
          }
          if (c1 == c) {
            ch->p = p1;
            queue[tail++] = ch;
            ans += ch->weight;
            break;
          }
        }
      }
    }
    dump(&root);
    return ans;
  }
};

