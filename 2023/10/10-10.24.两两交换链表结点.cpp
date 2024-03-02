
#include "vector"
#include <algorithm>
#include <iostream>
using namespace std;

//  Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
  ListNode *swapPairs(ListNode *head) {
    ListNode headNode(0, head);
    for (auto p = &headNode;
         p != nullptr && p->next != nullptr && p->next->next != nullptr;) {
      //   swapHead(p);
      auto a = p->next, b = p->next->next;
      p->next = b;
      a->next = b->next;
      b->next = a;
      // cout << p->val << '\t' << a->val << '\t' << b->val << endl;
      p = a;
    }
    return headNode.next;
  }
};

int main() {
  ListNode head(0);
  ListNode *phead = &head, *p = &head;
  vector<int> v{1, 2, 3, 4};
  for (auto x : v) {
    p->next = new ListNode(x);
    p = p->next;
  }
  for (p = head.next; p != nullptr; p = p->next) {
    cout << '\t' << p->val << '\t';
  }
  cout << endl;
  Solution s;
  s.swapPairs(phead);
  for (p = head.next; p != nullptr; p = p->next) {
    cout << '\t' << p->val << '\t';
  }
  cout << endl;
}
