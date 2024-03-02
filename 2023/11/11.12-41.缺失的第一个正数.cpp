#include <algorithm>
#include <ctime>
#include <deque> //  双端队列
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

// 给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
// 请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。
void heap_adjust(vector<int> &A, const int &n, int root) {
  int root_val = A[root - 1];

  for (int cur = root * 2; cur <= n; cur *= 2) {
    if (cur < n && A[cur] < A[cur - 1]) // 存在右节点，且右节点值较小
      ++cur;                            // 指向右节点
    if (root_val < A[cur - 1])
      break;
    else {
      A[root - 1] = A[cur - 1];
      root = cur;
    }
  }
  A[root - 1] = root_val;
}

class Solution1 {
public:
  int firstMissingPositive(vector<int> &A) {
    const int n = (int)A.size();
    for (auto i = n / 2; i > 0; --i) // 首先将A整理成小根堆
      heap_adjust(A, n, i);

    for (auto x : A) {
      cout << x << '\t';
    }
    int lower_bound = 0;
    for (int j = n; j > 0; --j) {
      if (A[0] > lower_bound + 1) {
        return lower_bound + 1;
      } else {
        lower_bound = max(lower_bound, A[0]);
        swap(A[0], A[j - 1]);     // 将最大的元素放到尾部
        heap_adjust(A, j - 1, 1); // 剩下j-1个元素重新调整为大根堆
      }
    }
    return lower_bound + 1;
  }
};

class Solution {
public:
  // 数组应当有 [1, 2, ..., N]的形式，即值为x的元素应当在x-1的位置上
  int firstMissingPositive(vector<int> &nums) {
    int n = (int)nums.size();
    for (int i = 0; i < n; ++i) {
      for (int x = nums[i], y = nums[x - 1]; x > 0 && x <= n && x != y;
           x = nums[i], y = nums[x - 1]) {
        swap(nums[i], nums[x - 1]);
      }
    }
    for (int i = 0; i < n; ++i) {
      if (nums[i] != i + 1) {
        return i + 1;
      }
    }
    return n + 1;
  }
};
void go() {
  vector<int> v{3, 4, 2, 1};
  auto n = Solution().firstMissingPositive(v);
  cout << endl << n;
}
int main() {
  clock_t begin = clock();
  go();
  clock_t end = clock();
  cout << endl << "exec cost " << (end - begin) << " us.";
}
