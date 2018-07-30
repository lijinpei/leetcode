#include <vector>
#include <string>
#include <forward_list>
#include <iostream>

struct Solution {
  int N, L, n;
  std::vector<int> n_adj;
  std::vector<std::forward_list<int>> adjs;
  std::vector<int> dist;
  std::vector<int> n_ways;
  struct Node {
    Node *sibling = nullptr;
    union {
      Node * child = nullptr;
      int n;
    };
    char c = 0;
  };
  Node * trie_root;
  bool inTrie(std::string & str) {
    Node *p = trie_root;
    for (int l = 0; l < L; ++l) {
      char ch = str[l];
      for (p = p->child; p; p = p->sibling) {
        if (p->c > ch) {
          return false;
        } else if (p->c == ch) {
          break;
        }
      }
    }
    return true;
  }
  Node* addFirstChild(Node *p, int l, std::string &str) {
    Node *c = new Node, *ret = c;
    c->sibling = p->child;
    p->child = c;
    c->c = str[l];
    for (++l; l < L; ++l) {
      c->child = new Node;
      c = c->child;
      c->sibling = nullptr;
      c->c = str[l];
    }
    c->n = n;
    return ret;
  }
  Node* addSibling(Node *s, int l, std::string &str) {
    Node * c = new Node;
    c->sibling = s->sibling;
    c->c = str[l];
    s->sibling = c;
    if (l + 1 != L) {
      addFirstChild(c, l + 1, str);
    } else {
      c->n = n;
    }
    return c;
  }
  void addAdj(Node* c, int l, std::string &str) {
    for (++l; l < L; ++l) {
      for (Node * ch = c->child; ch; ch = ch->sibling) {
        if (ch->c == str[l]) {
          c = ch;
          goto next_l;
        }
      }
      return;
    next_l:
      continue;
    }
    int m = c->n;
    ++n_adj[n];
    adjs[n].push_front(m);
    ++n_adj[m];
    adjs[m].push_front(n);
  }
  void addAdjs(Node* c, int l, std::string &str) {
    while (c) {
      addAdj(c, l, str);
      c = c->sibling;
    }
  }

  // add str to the trie, update n, str's adjs and n_adj
  void addToTrie(std::string & str) {
    Node * p = trie_root;
    for (int l = 0; l < L; ++l) {
      if (!p->child) {
        addFirstChild(p, l, str);
        ++n;
        return;
      } else if (p->child->c > str[l]) {
        Node * c = addFirstChild(p, l, str);
        addAdjs(c->sibling, l, str);
        ++n;
        return;
      } else {
        for (Node *c = p->child; c; c = c->sibling) {
          if (c->c == str[l]) {
            p = c;
            addAdjs(p->sibling, l, str);
            break;
          } else {
            addAdj(c, l, str);
            if (!c->sibling || c->sibling->c > str[l]) {
              p = addSibling(c, l, str);
              addAdjs(p->sibling, l, str);
              ++n;
              return;
            }
          }
        }
      }
    }
  }

  void buildTrie(std::vector<std::string>& wordList) {
    for (auto & str : wordList) {
      addToTrie(str);
    }
  }
  void init() {
    n = 0;
    trie_root = new Node;
    trie_root->child = nullptr;
    trie_root->sibling = nullptr;
    adjs.resize(N);
    n_adj.resize(N);
    dist.resize(N);
    n_ways.resize(N);
  }

  std::vector<std::vector<std::string>> DFS_distance(std::string & beginWord, std::string & endWord, std::vector<std::string> & wordList) {
    if (!inTrie(endWord)) {
      return {};
    }
    int diff = 0;
    for (int l = 0; l < L; ++l) {
      if (beginWord[l] != endWord[l]) {
        ++diff;
      }
    }
    if (1 == diff) {
      return {{beginWord, endWord}};
    }

    std::forward_list<int> end_adjs;
    int n0 = findAdjs(end_adjs, endWord);
    std::vector<int> DFS_queue(N);
    std::copy(end_adjs.begin(), end_adjs.end(), DFS_queue.begin());
    for (int i = 0; i < n0; ++i) {
      dist[DFS_queue[i]] = 1;
    }
    int m = 0, n = n0;
    while (m < n) {
      int p = DFS_queue[m++];
      int d = dist[p];
      for (auto c : adjs[p]) {
        if (!dist[c]) {
          dist[c] = d + 1;
          DFS_queue[n++] = c;
        }
      }
    }
    std::cout << std::endl;
    std::copy(end_adjs.begin(), end_adjs.end(), DFS_queue.begin());
    for (int i = 0; i < n0; ++i) {
      n_ways[DFS_queue[i]] = 1;
    }
    for (int i = n0; i < n; ++i) {
      int p = DFS_queue[i];
      int d = dist[p];
      int v = 0;
      for (auto c : adjs[p]) {
        if (d - 1 == dist[c]) {
          v += n_ways[c];
        }
      }
      n_ways[p] = v;
    }
    std::forward_list<int> begin_adjs;
    findAdjs(begin_adjs, beginWord);
    int min_dist = N + 1;
    int ways = 0;
    for (auto n : begin_adjs) {
      if (dist[n] < min_dist) {
        min_dist = dist[n];
        ways = n_ways[n];
      } else if (dist[n] == min_dist) {
        ways += n_ways[n];
      }
    }
    std::cerr << "min_dist: " << min_dist << std::endl;
    std::cerr << "ways: " << ways << std::endl;
    if (min_dist == N + 1) {
      return {};
    }
    std::vector<std::string> ret1(min_dist + 2);
    std::vector<std::vector<std::string>> ret;
    ret.reserve(ways);
    std::vector<std::pair<int, std::forward_list<int>::iterator>> stack(min_dist);
    int ss = 0;
    int ret_n = 0;
    ret1[0] = beginWord;
    ret1[min_dist + 1] = endWord;
    for (auto b : begin_adjs) {
        if (dist[b] != min_dist) {
          continue;
        }
        stack[0].first = b;
        stack[0].second = adjs[b].begin();
        ss = 1;

        while (ss) {
          auto & tos = stack[ss - 1];
          if (ss == min_dist) {
            for (int i = 0; i < min_dist; ++i) {
              ret1[i + 1] = wordList[stack[i].first];
            }
            ret.push_back(ret1);
            --ss;
            continue;
          }

          bool do_next = false;
          for (std::forward_list<int>::iterator ci = tos.second; ci != adjs[tos.first].end(); ++ci) {
            int c = *ci;
            if (dist[c] == min_dist - ss) {
              tos.second = ++ci;
              stack[ss].first = c;
              stack[ss].second = adjs[c].begin();
              ++ss;
              do_next = true;
              break;
            }
          }

          if (do_next) {
            continue;
          } else {
            --ss;
          }
        }
      }
    return ret;
  }

  template <typename C>
  int findAdjs1(C & adj, std::string & str, int l, Node *c) {
    for (++l; l < L; ++l) {
      char ch = str[l];
      bool find = false;
      for (c = c->child; c; c = c->sibling) {
        if (c->c == ch) {
          find = true;
          break;
        } if (c->c > ch) {
          break;
        }
      }
      if (!find) {
        return 0;
      }
    }
    adj.push_front(c->n);
    return 1;
  }

  template <typename C>
  int findAdjs(C & adj, std::string & str) {
    int ret = 0;
    Node * p = trie_root;
    for (int l = 0; l < L; ++l) {
      char ch = str[l];
      Node *c = p->child;
      p = nullptr;
      for (; c; c = c->sibling) {
        if (c->c == ch) {
          p = c;
        } else {
          ret += findAdjs1(adj, str, l, c);
        }
      }
      if (!p) {
        return ret;
      }
    }
    return ret;
  }

public:
  std::vector<std::vector<std::string>>
  findLadders(std::string beginWord, std::string endWord,
              std::vector<std::string> &wordList) {
    L = wordList[0].size();
    N = wordList.size();
    init();
    buildTrie(wordList);
    return DFS_distance(beginWord, endWord, wordList);
  }
};

int main() {
  std::vector<std::string> wordList;
  wordList.push_back(std::string("hot"));
  wordList.push_back(std::string("dot"));
  wordList.push_back(std::string("dog"));
  wordList.push_back(std::string("lot"));
  wordList.push_back(std::string("log"));
  //wordList.push_back(std::string("cog"));
  Solution sol;
  std::string beginWord = "hit", endWord = "cog";
  auto ret = sol.findLadders(beginWord, endWord, wordList);
  std::cerr << ret.size() << std::endl;
  /*
  std::cerr << sol.n << std::endl;
  for (auto & n : sol.n_adj) {
    std::cerr << n << ' ';
  }
  std::cerr << std::endl;
  std::cerr << "adjs: " << sol.adjs.size() << std::endl;
  for (auto  & adjs : sol.adjs) {
    for (auto & adj : adjs) {
      std::cerr << adj << ' ';
    }
    std::cerr << std::endl;
  }
  std::cerr << std::endl;
  */
}
