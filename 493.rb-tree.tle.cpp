#include <vector>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numeric>

template <typename P, size_t S, typename I>
class PointerIntPair {
  enum : uintptr_t {
    IntMask = (1 << S) - 1,
    PointerMask = ~IntMask
  };
  uintptr_t p;
  static uintptr_t U(P* p) {
    return uintptr_t(p);
  }
public:
  PointerIntPair() : p(U(nullptr)) {}
  PointerIntPair(P* p_) : p(U(p_)) {}
  // Note: this ctor doesn't check i_ overflow
  PointerIntPair(P *p_, I i_) : p(U(p_) | i_) {}
  I getInt() { return I(p & IntMask); }
  P* getPointer() { return reinterpret_cast<P*>(p & PointerMask); }
  void * getRaw() { return reinterpret_cast<void*>(p); }
  void setInt(I i_) { p = (p & PointerMask) | i_; }
  void setPointer(P *p_) { p = (p & IntMask) | U(p_); }
  void set(P *p_, I i_) { p = U(p_) | i_; }
};

enum ColorKind {
  CK_Red,
  CK_Black
};

class RBTreeNode {
  PointerIntPair<RBTreeNode, 1, int> parent; // bool = isLeftChild ?
  PointerIntPair<RBTreeNode, 1, ColorKind> left_child;
  RBTreeNode* right_child;
  RBTreeNode(int val_, ColorKind CK) : RBTreeNode(val_) {
    left_child.setInt(CK);
  }
  RBTreeNode(ColorKind CK, RBTreeNode *lc_, RBTreeNode *rc_) {
    left_child.set(lc_, CK);
    right_child = rc_;
  }
public:
  int val, child_count;
  RBTreeNode()
      : left_child(NIL(), CK_Red), right_child(NIL()), child_count(1) {}
  RBTreeNode(int val_)
      : parent(NIL()), left_child(NIL()), right_child(NIL()), val(val_) {}
  RBTreeNode* getParent() { return parent.getPointer(); }
  RBTreeNode* getLeftChild() { return left_child.getPointer(); }
  RBTreeNode* getRightChild() { return right_child; }
  ColorKind getColor() { return left_child.getInt(); }
  bool isLeftChild() { return parent.getInt(); }
  void setParent(RBTreeNode* p_) { parent.setPointer(p_); }
  void setLeftChild(RBTreeNode* l_) { left_child.setPointer(l_); }
  void setRightChild(RBTreeNode* r_) { right_child = r_; }
  void setColor(ColorKind c_) { left_child.setInt(c_); }
  void setIsRightChild() { parent.setInt(1); }
  void setIsLeftChild() { parent.setInt(0); }
  static RBTreeNode* NIL() {
    // only the color and address of this node is meaningful
    static RBTreeNode nil_node(CK_Black, nullptr, nullptr);
    return &nil_node;
  }
};

class Solution {
  static int findSmallerEqualCount(int v, RBTreeNode *p) {
    int ret = 0;
    for (RBTreeNode *e = RBTreeNode::NIL(); p !=e;) {
      if (p->val <= v) {
        ret += p->getLeftChild()->child_count + 1;
        p = p->getRightChild();
      } else {
        p = p->getLeftChild();
      }
    }
    return ret;
  }

  static RBTreeNode* insertNonBalanck(RBTreeNode * n, RBTreeNode* pp) {
    int v = n->val;
    while (true) {
      int v1 = pp->val;
      if (v >= v1) {
        RBTreeNode *npp = pp->getRightChild();
        if (npp != RBTreeNode::NIL()) {
          pp = npp;
        } else {
          pp->setRightChild(n);
          n->setParent(pp);
          n->setIsRightChild();
          n->setColor(CK_Red);
          return pp;
        }
      } else {
        RBTreeNode *npp = pp->getLeftChild();
        if (npp != RBTreeNode::NIL()) {
          pp = npp;
        } else {
          pp->setLeftChild(n);
          n->setParent(pp);
          n->setIsLeftChild();
          n->setColor(CK_Red);
          return pp;
        }
      }
    }
    return nullptr;
  }

  template <bool LR>
  static void setUpPC(RBTreeNode* p, RBTreeNode *c) {
    if (LR) {
      p->setLeftChild(c);
      p->child_count = c->child_count + p->getRightChild()->child_count + 1;
    } else {
      p->setRightChild(c);
      p->child_count = c->child_count + p->getLeftChild()->child_count + 1;
    }
    c->setParent(p);
  }

  template <bool UpdateCC = true>
  static void setUpPLR(RBTreeNode*p, RBTreeNode*l, RBTreeNode*r) {
    p->setLeftChild(l);
    p->setRightChild(r);
    l->setParent(p);
    r->setParent(p);
    if (UpdateCC) {
      p->child_count = l->child_count + r->child_count + 1;
    }
  }

  template <bool LR, bool PLR>
  static void rotate(RBTreeNode*& n, RBTreeNode*&pp, RBTreeNode*npp) {
    RBTreeNode* ppp = npp->getParent();
    int cc = npp->child_count;
    RBTreeNode *x = n->getLeftChild(), *y = n->getRightChild();
    RBTreeNode *z = LR ? pp->getRightChild() : pp->getLeftChild();
    bool pplr = npp->isLeftChild();
    auto newRoot = [&](RBTreeNode* r) {
      r->child_count = cc + 1;
      r->setParent(ppp);
      if (pplr) {
        ppp->setLeftChild(r);
      } else {
        ppp->setRightChild(r);
      }
    };
    if (LR ^ PLR) {
      if (LR) {
        setUpPC<false>(npp, x);
        setUpPLR(pp, y, z);
        setUpPLR<false>(n, npp, pp);
      } else {
        setUpPC<true>(npp, y);
        setUpPLR(pp, z, x);
        setUpPLR<false>(n, pp, npp);
      }
      pp->setColor(CK_Black);
      newRoot(n);
    } else {
      if (LR) {
        setUpPC<true>(npp, z);
        setUpPLR<false>(pp, n, npp);
      } else {
        setUpPC<false>(npp, z);
        setUpPLR<false>(pp, npp, n);
      }
      n->setColor(CK_Black);
      newRoot(pp);
    }
  }

  static void insert(RBTreeNode *n, RBTreeNode* rb_root) {
    RBTreeNode* pp = insertNonBalanck(n, rb_root);
    while (pp != RBTreeNode::NIL() && pp->getColor() == CK_Red) {
      RBTreeNode* npp = pp->getParent();
      if (npp == RBTreeNode::NIL()) {
        pp->setColor(CK_Black);
        ++pp->child_count;
        return;
      }
      bool lr = n->isLeftChild(), plr = pp->isLeftChild();
      RBTreeNode* uncle = plr ? npp->getRightChild() : npp->getLeftChild();
      if (uncle->getColor() == CK_Red) {
        uncle->setColor(CK_Black);
        pp->setColor(CK_Black);
        ++pp->child_count;
        ++npp->child_count;
        n = npp;
        pp = n->getParent();
        continue;
      }
      if (lr && plr) {
        rotate<true, true>(n, pp, npp);
      } else if (lr && !plr) {
        rotate<true, false>(n, pp, npp);
      } else if (!lr && plr) {
        rotate<false, true>(n, pp, npp);
      } else {
        rotate<false, false>(n, pp, npp);
      }
    }
    for (;pp != RBTreeNode::NIL(); pp = pp->getParent()) {
      ++pp->child_count;
    }
  }

  static int checkRBTree_impl(RBTreeNode *r) {
    if (r == RBTreeNode::NIL()) {
      return 0;
    }
    int ret = 1;
    if (r->getColor() == CK_Red) {
      if (r->getLeftChild()->getColor() != CK_Black || r->getRightChild()->getColor() != CK_Black) {
        std::cerr << "wrong 1\n";
      }
    }
    int v = r->val;
    //std::cout << v << ' ';
    RBTreeNode *rc = r->getRightChild(), *lc = r->getLeftChild();
    if (lc != RBTreeNode::NIL() && lc->val > v) {
        std::cerr << "wrong 2\n";
    } else {
      ret += checkRBTree_impl(lc);
    }
    if (rc != RBTreeNode::NIL() && rc->val < v) {
        std::cerr << "wrong 3\n";
    } else {
      ret += checkRBTree_impl(rc);
    }
    return ret;
  }

  static void checkRBTree(RBTreeNode *r, int n) {
    RBTreeNode *nil = RBTreeNode::NIL();
    if (nil->getColor() != CK_Black || nil->child_count != 0) {
        std::cerr << "wrong 0\n";
    }
    //std::cout << "tree value:\n";
    if (n != checkRBTree_impl(r)) {
        std::cerr << "wrong 4\n";
    }
    //std::cout << std::endl;
  }
public:
  int reversePairs(const std::vector<int> &nums) {
    size_t s  = nums.size();
    if (!s || s == 1) {
      return 0;
    }
    std::vector<RBTreeNode> storage(s - 1);
    size_t ss = 0;
    int ans = 0;
    RBTreeNode rb_root = RBTreeNode(nums[s - 1]);
    rb_root.setColor(CK_Black);
    for (size_t s1 = s - 1; s1; --s1) {
      //std::cout << "progress: " << s1 - 1 << std::endl;
      int v = nums[s1 - 1];
      int nv;
      if (!v) {
        nv = -1;
      } else if (v > 0) {
        nv = (v - 1) / 2;
      } else {
        nv = v / 2 - 1;
      }
      int nv1 = findSmallerEqualCount(nv, &rb_root);
      ans += nv1;
      storage[ss].val = v;
      insert(&storage[ss++], &rb_root);
      //checkRBTree(&rb_root, s - s1 + 1);
    }
    return ans;
  }
};

int main() {
  Solution sol;
  std::vector<int> input(50000);
  std::iota(input.begin(), input.end(), 0);
  std::cout << sol.reversePairs(input);
}
