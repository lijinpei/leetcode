/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
  ListNode* swapPairs(ListNode* head) {
    ListNode** lp = &head;
    ListNode* p1 = head, *p2;
    while (p1) {
      if ((p2 = p1->next) != nullptr) {
        *lp = p2;
        lp = &p1->next;
        std::swap(p1, p2->next);
      } else {
        *lp = p1;
        break;
      }
    }
    *lp = p1;
    return head;
  }
};
