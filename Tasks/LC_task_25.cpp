
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
  struct ListSpan {
    ListNode* first = nullptr;
    ListNode* last = nullptr;
  };

  static ListSpan Reverse(ListNode* begin, ListNode* end) {
    ListSpan result;
    result.last = begin;
    ListNode* next_node = begin;
    ListNode* curr_node = begin->next;
    while (curr_node != end) {
      ListNode* tmp = curr_node->next;
      curr_node->next = next_node;
      next_node = curr_node;
      result.first = curr_node;
      curr_node = tmp;
    }

    return result;
  }

 public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head || k == 1) return head;
    ListNode* root = nullptr;
    int count = 0;
    ListNode* prev_tail = nullptr;
    ListNode* first = head;
    while (head) {
      head = head->next;
      count++;
      if (!(count % k)) {
        ListSpan span = Reverse(first, head);
        // If it is the first reverse call -> store main root
        if (!prev_tail) {
          root = span.first;
        } else {
          prev_tail->next = span.first;
        }
        prev_tail = span.last;
        span.last->next = head;
        first = head;
      }
    }
    return root;
  }
};
