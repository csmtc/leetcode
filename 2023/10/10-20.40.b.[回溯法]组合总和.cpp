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
// 给定一个候选人编号的集合 candidates 和一个目标数 target ，找出 candidates
// 中所有可以使数字和为 target 的组合。 candidates
// 中的每个数字在每个组合中只能使用 一次 。 注意：解集不能包含重复的组合。
class Solution {
public:
  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    vector<vector<int>> result;
    vector<int> combination;
    sort(candidates.begin(), candidates.end());
    find_combination(candidates, target, 0, result, combination);
    return result;
  };
  void find_combination(vector<int> &candidates, int target, int begin,
                        vector<vector<int>> &result, vector<int> &combination) {
    if (target < 0)
      return;
    else if (target == 0) {
      vector<int> arr(combination);
      result.push_back(arr);
    } else {
      while (begin < candidates.size()) {
        auto x = candidates[begin];
        if(x>target)return;
        combination.push_back(x);
        find_combination(candidates, target - x, begin + 1, result,
                         combination);
        combination.pop_back();
        ++begin;
        while (begin < candidates.size() && x == candidates[begin])
          ++begin;
      }
    }
  }
};
inline void go() {
  vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
  int target = 8;
  auto result = Solution().combinationSum2(candidates, target);
  for (auto row : result) {
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
