// 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序
// 返回答案。

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

class SolutionV1 {
public:
  vector<vector<int>> permuteUnique(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    vector<int> cur;

    backtrack(nums, nums.size(), 0, result, &cur);
    return result;
  }

protected:
  
  int inline id(int x) { return x + 10; }
  void backtrack(vector<int> &nums, const int &n, const int pos,
                 vector<vector<int>> &result, vector<int> *cur) {
    if (pos == n) {
      result.push_back(*cur);
      cur = new vector<int>();
    } else {
      // 将题目给定的 n 个数的数组 nums划分成左右两个部分
      // 左边的表示已经填过的数，右边表示待填的数，我们在回溯的时候只要动态维护这个数组即可
      bool used_num[21]{false};
      for (int i = pos; i < n; ++i) { //下标为pos~n-1的是待填的数
        // 对于每个pos，不允许填入重复的数
        auto idx = id(nums[i]);
        if (used_num[idx])
          continue;
        used_num[idx] = true;
        cur->push_back(nums[i]), swap(nums[i], nums[pos]);
        backtrack(nums, n, pos + 1, result, cur);
        swap(nums[i], nums[pos]), cur->pop_back();
      }
    }
  }
};
class Solution {
public:
  vector<vector<int>> permuteUnique(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    vector<int> cur;

    backtrack(nums, nums.size(), 0, result, &cur);
    return result;
  }

protected:
  bool visit_idxs[9]{false};
  void backtrack(vector<int> &nums, const int &n, const int pos,
                 vector<vector<int>> &result, vector<int> *cur) {
    if (pos == n) {
      result.push_back(*cur);
      cur = new vector<int>();
    } else {
      for (int i = 0; i < n; ++i) { //下标为pos~n-1的是待填的数
        // 保证每次都是拿从左往右第一个未被填过的数字
        if (visit_idxs[i] || (i > 0 && nums[i] == nums[i - 1] && !visit_idxs[i - 1]))
          continue;
        
        cur->push_back(nums[i]), visit_idxs[i]=true;
        backtrack(nums, n, pos + 1, result, cur);
        visit_idxs[i]=false, cur->pop_back();
      }
    }
  }
};
inline void go() {
  vector<int> candidates = {0, 1, 0, 0, 9};
  auto result = Solution().permuteUnique(candidates);
  cout << "\n\n\n";
  for (auto & row : result) {
    for (auto x : row) {
      cout << x << '\t';
    }
    cout << endl;
  }
}
int main() {
  clock_t begin = clock();
  go();
  clock_t end = clock();
  cout << endl << "exec cost " << (end - begin) << " us.";
}
