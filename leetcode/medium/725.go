package main

type ListNode struct {
    Val int
    Next *ListNode
}

func listLen(root *ListNode) int {
  ret := 0
  for root != nil {
    ret++
    root = root.Next
  }
  return ret
}

func nList(root *ListNode, n int) *ListNode {
  for n > 1 {
    n--
    root = root.Next
  }
  ret := root.Next
  root.Next = nil
  return ret
}

func splitListToParts(root *ListNode, k int) []*ListNode {
  ret := make([]*ListNode, k)[0:0]
  l := listLen(root)
  n, m := l / k, l % k
  for i := 0; i < k; i++ {
    ret = append(ret, root)
    if root != nil {
      v := n
      if i < m {
        v++
      }
      root = nList(root, v)
    }
  }
  return ret
}

func main() {
}
