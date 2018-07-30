#include <iostream>
#include <vector>
#include <cstdint>

class Solution {
public:
  std::vector<std::vector<int>> pathSum(TreeNode *root, int target) {
    std::vector<std::vector<int>> ret;
    if (!root) {
      return ret;
    }
    std::vector<TreeNode*> stack;
    int sum = 0;
    auto clean = [](TreeNode* p) {
      return reinterpret_cast<TreeNode*>(uintptr_t(p) & ~uintptr_t(3));
    };
    auto pop = [&]() {
      sum -= clean(stack.back())->val;
      stack.pop_back();
    };
    auto push = [&](TreeNode* p) {
      stack.push_back(p);
      sum += p->val;
    };
    push(root);
    while (!stack.empty()) {
      //std::cout << sum << std::endl;
      auto & pi = *reinterpret_cast<uintptr_t*>(&stack.back());
      auto p = reinterpret_cast<TreeNode*>(pi & ~uintptr_t(3));
      //std::cout << std::hex << pi << std::dec << std::endl;
      //std::cout << p<< std::endl;
      //std::cout << stack.back() << std::endl;
      if (!(pi & uintptr_t(3))) {
        ++pi;
        if (p->left) {
          push(p->left);
          continue;
        }
      }
      if ((pi & 1) && (p->right)){
          ++pi;
          push(p->right);
      } else {
          //std::cout << sum << std::endl;
          //std::cout << "pi: " << (pi & uintptr_t(3)) << std::endl;
        if (sum == target && !(p->left || p->right)) {
          std::vector<int> tmp(stack.size());
          tmp.resize(0);
          for (TreeNode* p : stack) {
            tmp.push_back(clean(p)->val);
          }
          ret.push_back(tmp);
        }
        pop();
      }
    }
    return ret;
  }
};


