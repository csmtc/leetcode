// 给你一个整数数组 nums，有一个大小为 k
// 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k
// 个数字。滑动窗口每次只向右移动一位。

// 返回 滑动窗口中的最大值 。
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
// 对窗口中的元素排序，
class Solution {
public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    int p = -1, n = nums.size();
    // win中元素 下标升序，值降序（从而可以将尾部所有较小的值丢掉）
    deque<pair<int, int>> win;
    vector<int> ret;
    // while (++p < k) {
    //   win.push_back()
    // }

    while (++p < n) {
      auto val = nums[p];
      // 移除尾部小元素
      while (!win.empty() && val >= win.back().second)
        win.pop_back();
      win.push_back({p, val});
      if (p >= k - 1)
        ret.push_back(win.front().second);
      // 滑动一个元素
      if (p >= k && win.front().first == p - k) {
        win.pop_front();
      }
    }
    if (!win.empty())
      ret.push_back(win.front().second);
    return ret;
  }
};

inline void go() {
  vector<int> arr = {-7, -8, 7, 5, 7, 1, 6, 0};
  auto ret = Solution().maxSlidingWindow(arr, 4);
  for (auto x : ret)
    cout << x << '\t';
}
int main() {
  clock_t begin = clock();
  go();
  clock_t end = clock();
  cout << endl << "exec cost " << (end - begin) << " us.";
}