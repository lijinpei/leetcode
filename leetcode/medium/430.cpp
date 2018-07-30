class Node {
public:
    int val;
    Node* prev = nullptr;
    Node* next = nullptr;
    Node* child = nullptr;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};

class Solution {
  static Node* flatten_impl(Node* head) {
    if (!head) {
      return nullptr;
    }
    while (true) {
      auto* head1 = head->next;
      if (head->child) {
        auto* tail = flatten_impl(head->child);
        head->child->prev = head;
        head->next = head->child;
        head->child = nullptr;
        if (!head1) {
          return head;
        }
        tail->next = head1;
        head1->prev = tail;
      }
      if (!head1) {
        return head;
      }
      head = head1;
    }
  }
public:
  Node* flatten(Node* head) {
    flatten_impl(head);
    return head;
  }
};
