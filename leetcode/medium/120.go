package main

func minimumTotal(triangle [][]int) int {
  n := len(triangle)
  dp := make([]int, n)
  for i := 0; i < n; i++ {
    lv := dp[0]
    dp[0] = dp[0] + triangle[i][0]
    for j := 1; j < i; j++ {
      llv := dp[j]
      if llv < lv {
        dp[j] = llv + triangle[i][j]
      } else {
        dp[j] = lv + triangle[i][j]
      }
      lv = llv
    }
    if i != 0 {
      dp[i] = lv + triangle[i][i]
    }
  }
  ans := dp[0]
  for i := 1; i < n; i++ {
    v := dp[i]
    if v < ans {
      ans = v
    }
  }
  return ans
}

func main() {
}
