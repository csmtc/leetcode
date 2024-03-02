// 整数数组 nums 按升序排列，数组中的值 互不相同 。

// 在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了
// 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ...,
// nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3
// 处经旋转后可能变为 [4,5,6,7,0,1,2] 。

// 给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target
// ，则返回它的下标，否则返回 -1 。

// 你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。

#include <algorithm>
#include <deque> //  双端队列
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <time.h>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
class Solution {
public:
  int search(vector<int> &nums, int target) {
    int idx = -1;
    search_(nums, target, 0, nums.size() - 1, idx);
    return idx;
  }

  void search_(vector<int> &A, int &t, int l, int r, int &idx) {
    // target在l~r区间的几种情况,||表示分界线，大写字母表示所在下标处的元素值
    // 1. l t r ||或 || l t r   L<T<R
    // 2. l t || r              R<L<T
    // 3. l || t r              T<R<L
    if (l >= r || idx != -1) {
      if (l == r && A[l] == t)
        idx = l;
      return;
    }
    if (A[l] <= t && t <= A[r] || A[r] <= A[l] && A[l] <= t ||
        t <= A[r] && A[r] <= A[l]) {
      int m = (l + r) / 2;
      if (A[m] == t)
        idx = m;
      search_(A, t, l, m, idx);
      search_(A, t, m+1, r, idx);
    } else
      return;
  }
};
inline void go() {
  vector<int> A{1,3};
  cout << Solution().search(A, 2);
}
int main() {
  clock_t begin = clock();
  go();
  clock_t end = clock();
  cout << endl << "exec cost " << (end - begin) << " us.";
}