class Solution {
public:
  bool reachingPoints(int sx, int sy, int tx, int ty) {
    while (true) {
      if (sx == tx) {
        return 0 == (ty - sy) % sx;
      }
      if (tx < sx) {
        return false;
      }
      if (sy == ty) {
        return 0 == (tx - sx) % sy;
      }
      if (ty < sy) {
        return false;
      }
      if (tx < ty) {
        ty %= tx;
      } else {
        tx %= ty;
      }
    }
  }
};
