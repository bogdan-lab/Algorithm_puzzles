#include <algorithm>
#include <vector>

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

bool NodeHeapCompare(const ListNode* lhs, const ListNode* rhs) {
  return lhs->val > rhs->val;
}
class Solution {
 public:
  ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    std::vector<ListNode*> queue;
    queue.reserve(lists.size());
    for (const auto& el : lists) {
      if (el) queue.push_back(el);
    }
    if (queue.empty()) return nullptr;
    std::make_heap(queue.begin(), queue.end(), NodeHeapCompare);

    std::pop_heap(queue.begin(), queue.end(), NodeHeapCompare);
    ListNode* head = queue.back();
    ListNode* curr_node = head;
    if (queue.back()->next) {
      queue.back() = queue.back()->next;
      std::push_heap(queue.begin(), queue.end(), NodeHeapCompare);
    } else {
      queue.pop_back();
    }

    while (!queue.empty()) {
      std::pop_heap(queue.begin(), queue.end(), NodeHeapCompare);
      curr_node->next = queue.back();
      curr_node = curr_node->next;
      if (queue.back()->next) {
        queue.back() = queue.back()->next;
        std::push_heap(queue.begin(), queue.end(), NodeHeapCompare);
      } else {
        queue.pop_back();
      }
    }
    return head;
  }
};
