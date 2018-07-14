type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

func insertIntoBST(root *TreeNode, val int) *TreeNode {
  if root == nil {
    return &TreeNode{val, nil, nil}
  }
  ret := root
  for {
    v := root.Val
    if val < v {
      if root.Left != nil {
        root = root.Left
      } else {
        root.Left = &TreeNode{val, nil, nil}
        break
      }
    } else {
      if root.Right != nil {
        root = root.Right
      } else {
        root.Right = &TreeNode{val, nil, nil}
        break
      }
    }
  }
  return ret
}
