func oddEvenList(head *ListNode) *ListNode {
  if head == nil {
    return nil
  }
  head2 := head.Next
  if head2 == nil {
    return head
  }
  tail1, tail2 := head, head2
  for tail2.Next != nil {
    tail1, tail1.Next = tail2.Next, tail2.Next
    if tail1.Next != nil {
      tail2, tail2.Next = tail1.Next, tail1.Next
    } else {
      tail2.Next = nil
      break
    }
  }
  tail1.Next = head2
  return head
}
