// 给你一个按照非递减顺序排列的整数数组 nums，和一个目标值
// target。请你找出给定目标值在数组中的开始位置和结束位置。

// 如果数组中不存在目标值 target，返回 [-1, -1]。

// 你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。

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

// 全用2分
class SolutionV1 {
public:
  vector<int> searchRange(vector<int> &A, int target) {
    int lo = 0, hi = A.size() - 1, mid = 0;
    vector<int> ret{-1, -1};

    // 二分查找target
    while (lo <= hi) {
      mid = (lo + hi) / 2;
      if (target == A[mid]) {
        auto hi_ = hi, mid_ = mid;
        // 在lo->mid查找左边界
        for (hi = mid; lo <= hi;) {
          mid = (lo + hi) / 2;
          if (target == A[mid])
            hi = mid - 1, ret[0] = mid;
          else
            lo = mid + 1;
        }
        // 在mid->hi查找右边界
        for (lo = mid_, hi = hi_; lo <= hi;) {
          mid = (lo + hi) / 2;
          if (target == A[mid])
            lo = mid + 1, ret[1] = mid;
          else
            hi = mid - 1;
        }
        return ret;
      } else if (target < A[mid])
        hi = mid - 1;
      else
        lo = mid + 1;
    }

    return ret;
  }
};

// 二分+线序
class Solution {
public:
  vector<int> searchRange(vector<int> &A, int target) {
    int lo = 0, hi = A.size() - 1, mid = 0;
    vector<int> ret{-1, -1};

    // 二分查找target
    while (lo <= hi) {
      mid = (lo + hi) / 2;
      if (target == A[mid]) {
        // 在lo->mid查找左边界
        while (A[lo] < target)
          ++lo;
        ret[0] = lo;
        // 在mid->hi查找右边界
        while (A[hi] > target)
          --hi;
        ret[1] = hi;
        return ret;
      } else if (target < A[mid])
        hi = mid - 1;
      else
        lo = mid + 1;
    }
    return ret;
  }
};
inline void go() {
  vector<int> V{5,7,7,8,8,10};
  auto S = Solution().searchRange(V, 8);
  for (auto x : S)
    cout << x << '\t';
}

int main() {
  clock_t begin = clock();
  go();
  clock_t end = clock();
  cout << endl << "exec cost " << (end - begin) << " us.";
}