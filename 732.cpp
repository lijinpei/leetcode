#include <algorithm>

struct SegmentTreeNode {
  int max, debt;
  SegmentTreeNode *left_child, *right_child;
  SegmentTreeNode(SegmentTreeNode* lc, SegmentTreeNode* rc) : max(0), debt(0), left_child(lc), right_child(rc) {}
};

static int M(int l, int r) { return ((r - l) >> 1) + l; }

SegmentTreeNode *buildSegmentTree() {
  return new SegmentTreeNode(nullptr, nullptr);
}

void segmentInc(int l, int r, SegmentTreeNode *root, int l0, int r0) {
  if (l >= r0 || r <= l0) {
    return;
  }
  if (l <= l0 && r >= r0) {
    ++root->debt;
    ++root->max;
    return;
  }
  if (root->left_child == nullptr) {
    root->left_child = buildSegmentTree();
  }
  if (root->right_child == nullptr) {
    root->right_child = buildSegmentTree();
  }
  root->left_child->debt += root->debt;
  root->left_child->max += root->debt;
  root->right_child->debt += root->debt;
  root->right_child->max += root->debt;
  root->debt = 0;
  int m0 = M(l0, r0);
  segmentInc(l, r, root->left_child, l0, m0);
  segmentInc(l, r, root->right_child, m0, r0);
  root->max = std::max(root->left_child->max, root->right_child->max);
}

class MyCalendarThree {
  static const int l0 = 0, r0 = 1000000001;
  SegmentTreeNode *root;

public:
  MyCalendarThree() : root(buildSegmentTree()) {}

  int book(int start, int end) {
    segmentInc(start, end, root, l0, r0);
    return root->max;
  }
};
