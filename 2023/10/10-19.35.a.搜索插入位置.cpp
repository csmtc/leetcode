// 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

// 请必须使用时间复杂度为 O(log n) 的算法。

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
  int searchInsert(vector<int> &A, int target) {
    int lo = 0, hi = A.size() - 1, m;
    while (lo <= hi) {
      m = (lo+hi)/2;
      if (A[m] == target) {
        return m;
      } else if (target < A[m]) {
        hi = m - 1;
      } else {
        lo = m + 1;
      }
    }
    return lo;
  }
};
inline void go() {
  vector<int> A{1, 3, 5, 6};
  cout << Solution().searchInsert(A, 2);
}
int main() {
  clock_t begin = clock();
  go();
  clock_t end = clock();
  cout << endl << "exec cost " << (end - begin) << " us.";
}