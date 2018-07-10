package main

type ListNode struct {
   Val int
   Next *ListNode
}

type TreeNode struct {
   Val int
   Left *TreeNode
   Right *TreeNode
}
 

func sortedListToBST_impl(head * ListNode, l int) (*TreeNode, *ListNode) {
  if 1 == l {
    return &TreeNode{head.Val, nil, nil}, head
  }
  ln := l / 2
  lt, root := sortedListToBST_impl(head, ln)
  root = root.Next
  t := root
  var rt *TreeNode = nil
  if l > ln + 1 {
    rt, t = sortedListToBST_impl(root.Next, l - ln - 1)
  }
  root_node := &TreeNode{root.Val, lt, rt}
  return root_node, t
}

func listLen(head* ListNode) int {
  ret := 1
  for ; head.Next != nil; {
    head = head.Next
    ret++
  }
  return ret
}

func sortedListToBST(head *ListNode) *TreeNode {
  if head == nil {
    return nil
  }
  l := listLen(head)
  ret, _ := sortedListToBST_impl(head, l)
  return ret
}

func main() {
}
