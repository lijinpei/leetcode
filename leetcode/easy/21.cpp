class Solution {
public:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1) {
      return l2;
    }
    if (!l2) {
      return l1;
    }
    ListNode *head;
    if (l1->val < l2->val) {
      head = l1;
      l1 = l1->next;
    } else {
      head = l2;
      l2 = l2->next;
    }
    ListNode* ret = head;
    while (l1 && l2) {
      if (l1->val < l2->val) {
        head = head->next = l1;
        l1 = l1->next;
      } else {
        head = head->next = l2;
        l2 = l2->next;
      }
    }
    if (!l1) {
      head->next = l2;
    } else {
      head->next = l1;
    }
    return ret;
  }
};
