

// 给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
// k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k
// 的整数倍，那么请将最后剩余的节点保持原有顺序 要求只用 O(1) 额外内存空间

#include <algorithm>
#include <iostream>

#include "vector"
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
  ListNode *reverseKGroup(ListNode *head, int k) {
    int cnt = 0;
    for (ListNode *left = nullptr, *right = head, *tmp; right;) {
      if (++cnt == k) {
        tmp = right->next;
        // cout << endl << left->val << ',' << right->val;
        if (left == nullptr) {
          // 第一次
          left = reverse(head, right->next);
        } else {
          left = reverse(left->next, right->next);
        }
        right = tmp;
        cnt = 0;
      } else {
        right = right->next;
      }
    }
    // cout << endl << endl;
    // for (auto p = head; p != nullptr; p = p->next) {
    //   cout << '\t' << p->val << '\t';
    // }
    return head;
  }

  // 没头结点，返回尾结点
  ListNode * reverse(ListNode *&begin, ListNode *end = nullptr) {
    if (begin==end)
      return nullptr;
    else if (begin->next==end)
      return begin;
    // 至少有head,head->next 2个结点
    ListNode *tail = begin->next, *p = begin->next, *q;
    begin->next = nullptr;
    while (p != end) {
      q = p->next;
      // insert p
      p->next = begin->next;
      begin->next = p;
      p = q;
    }
    tail->next = begin;
    tail = begin;
    begin = begin->next;
    tail->next = end;
    // for (p = begin; p != end; p = p->next) {
    //   cout << '\t' << p->val << '\t';
    // }
    return tail;
  }
};

int main() {
  ListNode head(0);
  ListNode *phead = &head, *p = &head;
  vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (auto x : v) {
    p->next = new ListNode(x);
    p = p->next;
  }
  for (p = phead; p != nullptr; p = p->next) {
    cout << '\t' << p->val << '\t';
  }
  cout << endl;
  Solution s;
  //   s.reverse(phead);
  phead = s.reverseKGroup(phead, 1);
  cout << endl;
  for (p = phead; p != nullptr; p = p->next) {
    cout << '\t' << p->val << '\t';
  }
}