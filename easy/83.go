func deleteDuplicates(head *ListNode) *ListNode {
  if head == nil {
    return nil
  }
  ret := head 
  ln := head
  lv := head.Val
  head = head.Next
  for head != nil {
    if lv != head.Val {
      ln.Next = head 
      ln = head
      lv = head.Val
    }
    head = head.Next
  }
  ln.Next = head
  return ret
}
