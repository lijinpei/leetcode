#include <iostream>
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
 
class Solution {
public:
  ListNode* sortList(ListNode* head) {
    int n = 0;
    for (ListNode* p = head; p; p = p->next) {
      ++n;
    }
    auto next = [](ListNode* p, int n) -> ListNode* {
      if (!p) {
        return nullptr;
      }
      while (--n) {
        ListNode* np = p->next;
        if (np) {
          p = np;
        } else {
          break;
        }
      }
      return p;
    };
    for (int l = 1; l <= n; l += l) {
      ListNode** lp = &head;
      ListNode* p1 = head, *pe1 = next(p1, l), *p2 = pe1->next, *pe2 = next(p2, l), *np;
      while (p2) {
        np = pe2->next;
        bool b1 = true, b2 = true;
        while (b1 && b2) {
          if (p1->val < p2->val) {
            *lp = p1;
            lp = &p1->next;
            b1 = p1 != pe1;
            p1 = p1->next;
          } else {
            *lp = p2;
            lp = &p2->next;
            b2 = p2 != pe2;
            p2 = p2->next;
          }
        }
        if (!b1) {
          *lp = p2;
          lp = &pe2->next;
        } else {
          *lp = p1;
          lp = &pe1->next;
        }
        p1 = np;
        if (!p1) {
          break;
        }
        pe1 = next(p1, l);
        p2 = pe1->next;
        pe2 = next(p2, l);
      }
      *lp = p1;
    }
    return head;
  }
};
