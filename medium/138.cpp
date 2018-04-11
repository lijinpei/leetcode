struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(nullptr), random(nullptr) {}
};

class Solution {
public:
  RandomListNode *copyRandomList(RandomListNode *head) {
    if (!head) {
      return nullptr;
    }
    for (RandomListNode* p = head, *np; p; p = np) {
      np = p->next;
      p->next = new RandomListNode(p->label);
      p->next->next = np;
    }
    for (auto* p = head, *np = p->next; ;) {
      auto * r = p->random;
      np->random = r ? r->next : nullptr;
      if (np->next) {
        p = np->next;
        np = p->next;
      } else {
        break;
      }
    }
    auto* ret = head->next;
    for (auto* p = head, *np = p->next; ;) {
      p = p->next = np->next;
      if (p) {
        np = np->next = p->next;
      } else {
        np->next = nullptr;
        break;
      }
    }
    return ret;
  }
};

int main() {
  RandomListNode r(-1);
  Solution sol;
  sol.copyRandomList(&r);
}
