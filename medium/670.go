func maximumSwap(num int) int {
  num0 := num
  digits := [9]int{}
  s := 0
  for num > 0 {
    digits[s] = num % 10
    num /= 10
    s++
  }
  for i := s - 1; i >= 0; i-- {
    d := digits[i]
    md := d
    mp := i
    for j := i - 1; j >= 0; j-- {
      nd := digits[j]
      if nd >= md {
        md = nd
        mp = j
      }
    }
    if d != md {
      digits[i], digits[mp] = digits[mp], digits[i]
      ret := 0
      for i := s - 1; i >= 0; i-- {
        ret = ret * 10 + digits[i]
      }
      return ret
    }
  }
  return num0
}
