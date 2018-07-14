package main

import (
  "fmt"
)

var n, m int
var flags []uint64
var matrix [][]int

func calc(x, y int) (l1, l2 uint) {
  var l uint = uint(x * m + y) * uint(2)
  l1, l2 = l / uint(64), l % uint(64)
  return
}

func set1(x, y int) {
  l1, l2 := calc(x, y)
  flags[l1] = flags[l1] | (uint64(1) << l2)
}

func test1(x, y int) bool {
  if x < 0 || x >= n || y < 0 || y >= m {
    return false
  }
  l1, l2 := calc(x, y)
  return (flags[l1] & (uint64(1) << l2)) == 0
}

func set2(x, y int) {
  l1, l2 := calc(x, y)
  l2 = l2 + 1
  flags[l1] = flags[l1] | (uint64(1) << l2)
}

func test2(x, y int) bool {
  if x < 0 || x >= n || y < 0 || y >= m {
    return false
  }
  l1, l2 := calc(x, y)
  l2 = l2 + 1
  return (flags[l1] & (uint64(1) << l2)) == 0
}

type test func(int, int) bool;
type set func(int, int);

func resize(n_, m_ int) {
  n, m = n_, m_
  flags = make([]uint64, (n * m + 63) / 64)
}

func dfs(x, y int, t test, s set) {
  s(x, y)
  h := matrix[x][y]
  try := func(x1, y1 int) {
    if t(x1, y1) && matrix[x1][y1] >= h {
      dfs(x1, y1, t, s)
    }
  }
  try(x - 1, y)
  try(x + 1, y)
  try(x, y - 1)
  try(x, y + 1)
}

func pacificAtlantic(matrix_ [][]int) [][]int {
  matrix = matrix_[:]
  fmt.Println(len(matrix)) 
  fmt.Println(len(matrix[0])) 
  resize(len(matrix), len(matrix[0]));
  for i := 0; i < n; i++ {
    for j := 0; j < m; j++ {
      fmt.Print(matrix[i][j], ' ')
    }
    fmt.Println()
  }
  for i := 0; i < n; i++ {
    dfs(i, 0, test1, set1)
    dfs(i, m - 1, test1, set1)
  }
  for i := 0; i < m; i++ {
    dfs(0, i, test1, set1)
    dfs(n - 1, i, test1, set1)
  }
  ret := make([][]int, n * m)[0:0]
  for i := 0; i < n; i++ {
    for j := 0; j < m; j++ {
      if test1(i, j) && test2(i, j) {
        fmt.Println(i, j)
        ret = append(ret, []int{i, j})
      }
    }
  }
  return ret
}

func main() {
  var input [][]int
  input = append(input, []int{1, 2, 2, 3, 5})
  input = append(input, []int{3, 2, 3, 4, 4})
  input = append(input, []int{2, 4, 5, 3, 1})
  input = append(input, []int{6, 7, 1, 4, 5})
  input = append(input, []int{5, 1, 1, 2, 4})
  fmt.Println(len(input))
  pacificAtlantic(input[:])
}
