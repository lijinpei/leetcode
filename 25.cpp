#include <iostream>
#include <utility>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode *reverseKGroup(ListNode *h, int k) {
    if (1 == k) {
      return h;
    }
    ListNode head(-1);
    head.next = h;
    h = &head;
    ListNode *e;
    auto nxt = [](ListNode* p, int k) {
      while (k-- && p) {
        p = p->next;
      }
      return p;
    };
    auto rev = [](ListNode* h, ListNode* e, int k) {
      ListNode* ret = h->next;
      h->next = e;
      e = e->next;
      ListNode* h1 = ret;
      while (k--) {
        ListNode* tmp = h1->next;
        h1->next = e;
        e = h1;
        h1 = tmp;
      }
      return ret;
    };
    while (true) {
      e = nxt(h, k);
      if (!e) {
        break;
      }
      h = rev(h, e, k);
    }
    return head.next;
  }
};
