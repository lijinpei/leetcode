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
  ListNode* partition(ListNode* head, int x) {
    ListNode dummy_left(-1), dummy_right(-1);
    ListNode *left = &dummy_left, *right = &dummy_right;
    for (ListNode* p = head; p; p = p->next) {
      if (p->val < x) {
        left->next = p;
        left = p;
      } else {
        right->next = p;
        right = p;
      }
    }
    right->next = nullptr;
    if (left != &dummy_left) {
      left->next = dummy_right.next;
      return dummy_left.next;
    } else {
      return dummy_right.next;
    }
  }
};
