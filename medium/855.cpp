#include <set>

class ExamRoom {
  int N;
  std::set<int> pos;

public:
  ExamRoom(int N) : N(N) {}

  int seat() {
    if (pos.empty()) {
      pos.insert(0);
      return 0;
    }
    int mp = 0;
    int md = *pos.begin(), lp = md;
    for (int p : pos) {
      int np = (p + lp) / 2;
      int nd = np - lp;
      if (nd > md) {
        md = nd;
        mp = np;
      }
      lp = p;
    }
    if (N - 1 - lp > md) {
      mp = N - 1;
    }
    pos.insert(mp);
    return mp;
  }

  void leave(int p) {
    pos.erase(p);
  }
};
