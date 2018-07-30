struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
      ListNode* p0 = head;
      ListNode** lp = &head;
      while (p0) {
        int val = p0->val;
        ListNode* p1 = p0->next;
        if (!p1 || p1->val != val) {
          *lp = p0;
          lp = &(p0->next);
          p0 = p1;
        } else {
          do {
            p1 = p1->next;
          } while (p1 && p1->val == val);
          p0->next = p1;
          p0 = p1;
        }
      }
      *lp = nullptr;
      return head;
    }
};
