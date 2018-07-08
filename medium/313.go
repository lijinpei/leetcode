package main

import (
  "fmt"
)

var n, k int
var primes []int
var arr []int
type pq_node struct  {
  v, p, pr int
}

var pq []pq_node

func down(p int) {
  k := len(pq)
  if p >= k {
    return
  }
  for {
    lc := 2 * p + 1
    if lc >= k {
      break
    }
    if pq[lc].v < pq[p].v {
      rc := lc + 1
      if rc >= k || pq[lc].v < pq[rc].v {
        pq[p], pq[lc] = pq[lc], pq[p]
        p = lc
      } else {
        pq[p], pq[rc] = pq[rc], pq[p]
        p = rc
      }
      continue
    }
    rc := lc + 1
    if rc >= k {
      break
    }
    if pq[rc].v < pq[p].v {
      pq[p], pq[rc] = pq[rc], pq[p]
      p = rc
    } else {
      break
    }
  }
}

func up(p int) {
  for p != 0 {
    fa := (p - 1) / 2
    if pq[p].v < pq[fa].v {
      pq[p], pq[fa] = pq[fa], pq[p]
      p = fa
    } else {
      break
    }
  }
}

func inc() {
  p, pr := pq[0].p, pq[0].pr
  pq[0] = pq_node{v:pr * arr[p], p:p + 1, pr:pr}
  down(0)
}

func nthSuperUglyNumber(n_ int, primes_ []int) int {
  n = n_
  primes = primes_
  k = len(primes)
  arr = make([]int, n)
  arr[0] = 1
  pq = make([]pq_node, k)[0:0]
  for i := 0; i < k; i++ {
    pq = append(pq, pq_node{v:primes[i], p:1, pr:primes[i]})
  }
  lv := 1
  for i := 1; i < n; i++ {
    for lv == pq[0].v {
      inc()
    }
    arr[i] = pq[0].v
    lv = arr[i]
    inc()
  }
  /*
  for i := 0; i < n; i++ {
    fmt.Println(i, arr[i])
  }
  */
  return arr[n - 1]
}

func main() {
  input := [...]int{2, 7, 13, 19}
  fmt.Println(nthSuperUglyNumber(12, input[:]))
}
