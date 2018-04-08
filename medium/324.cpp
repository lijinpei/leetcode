#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>

class Solution {
public:
  void wiggleSort(std::vector<int> &nums) {
    int n = nums.size();
    std::nth_element(nums.begin(), nums.begin() + (n >> 1), nums.end());
    int m = nums[n >> 1];
    //std::cout << m << std::endl;
    auto inc = [&](int & p) {
      p += 2;
      if (p >= n) {
        p = 0;
      }
    };
    int n1 = 0, n2 = 0, n3 = 0;
    for (auto v : nums) {
      if (v < m) {
        ++n1;
      } else if (v == m) {
        ++n2;
      } else {
        ++n3;
      }
    }
    //std::cout << n1 << ' ' << n2 << ' ' << n3 << std::endl;
    int i = 1, j = 2 * n3 - 1, k = (n & 1 ? n - 1 : n - 2);
    inc(j);
    /*
    std::cout << i << ' ' << j << ' ' << k << std::endl;
      for (auto v : nums) {
        std::cout << v << ' ';
      }
      std::cout << std::endl;
      */
    while (n1 || n3) {
      if (n3) {
        while (n3) {
          int v1 = nums[i];
          if (v1 > m) {
            i += 2;
            --n3;
          } else if (v1 == m) {
            while (nums[j] == m) {
              --n2;
              inc(j);
            }
            std::swap(nums[j], nums[i]);
            --n2;
            inc(j);
          } else {
            break;
          }
        }
      }
      if (n1) {
        while (n1) {
          int v1 = nums[k];
          if (v1 < m) {
            k -= 2;
            --n1;
          } else if (v1 == m) {
            while (nums[j] == m) {
              --n2;
              inc(j);
            }
            std::swap(nums[j], nums[k]);
            --n2;
            inc(j);
          } else {
            break;
          }
        }
      }
      if (n1 && n3) {
        std::swap(nums[i], nums[k]);
        i += 2;
        --n3;
        k -= 2;
        --n1;
      }
      /*
      std::cout << n1 << ' ' << n2 << ' ' << n3 << std::endl;
      for (auto v : nums) {
        std::cout << v << ' ';
      }
      std::cout << std::endl;
      */
    }
  }
};

int main() {
  Solution sol;
  //std::vector<int> input{1, 5, 1, 1, 6, 4};
  //std::vector<int> input{1, 3, 2, 2, 3, 1};
  //std::vector<int> input{4, 5, 5, 6};
  //std::vector<int> input{1, 1, 2, 2, 2, 1};
  //std::vector<int> input{1, 1, 2, 1, 2, 2, 1};
  std::vector<int> input{5,3,1,2,6,7,8,5,5};
  sol.wiggleSort(input);
  for (auto v : input) {
    std::cout << v << ' ';
  }
  std::cout << std::endl;
}
