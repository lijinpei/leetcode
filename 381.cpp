#include <vector>
#include <unordered_map>
#include <utility>
#include <cstdlib>

class RandomizedCollection {
  std::vector<std::pair<int, int>> V;
  std::unordered_map<int, std::vector<int>> S;
  int size;
public:
  /** Initialize your data structure here. */
  RandomizedCollection() : size(0) {}

  /** Inserts a value to the collection. Returns true if the collection did not
   * already contain the specified element. */
  bool insert(int val) {
    ++size;
    auto & v = S[val];
    int s0 = v.size();
    v.push_back(V.size());
    V.emplace_back(val, s0);
    return !s0;
  }

  /** Removes a value from the collection. Returns true if the collection
   * contained the specified element. */
  bool remove(int val) {
    auto & v = S[val];
    if (v.empty()) {
      return false;
    }
    --size;
    int i = v.back();
    v.pop_back();
    int s0 = V.size();
    if (i + 1 != s0) {
      auto b = V.back();
      V[i] = b;
      S[b.first][b.second] = i;
    }
    V.pop_back();
    return true;
  }

  /** Get a random element from the collection. */
  int getRandom() {
    /* warning: this method of generating uniform distribution is incorrect. */
    return V[rand() % size].first;
  }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
