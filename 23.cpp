#include <vector>
#include <queue>
#include <utility>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    using T = std::pair<int, ListNode*>;
    int s = lists.size();
    std::vector<T> pq_container(s);
    int left = 0;
    for (int i = 0; i < s; ++i) {
      if (lists[i]) {
        pq_container[left++] = T(lists[i]->val, lists[i]);
      }
    }
    if (!left) {
      return nullptr;
    }
    if (left == 1) {
      return pq_container[0].second;
    }
    pq_container.resize(left);
    std::vector<int> pq_head(s, 0);
    auto pq_compare = [](const T & v1, const T & v2) {
      return v1.first > v2.first;
    };
    std::priority_queue<T, decltype(pq_container), decltype(pq_compare)> pq(
        pq_compare, pq_container);
    auto replace_top = [&]() {
      T n = pq.top();
      pq.pop();
      if (n.second->next) {
        pq.push(T(n.second->next->val, n.second->next));
      } else {
        --left;
      }
      return n.second;
    };
    ListNode* ret = replace_top(), *last = ret;
    while (left != 1) {
      last->next = replace_top();
      last = last->next;
    }
    last->next = pq.top().second;
    return ret;
  }
};

