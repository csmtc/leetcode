// 给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出
// candidates 中可以使数字和为目标数 target 的 所有 不同组合
// ，并以列表形式返回。你可以按 任意顺序 返回这些组合。

// candidates 中的 同一个 数字可以 无限制重复被选取
// 。如果至少一个数字的被选数量不同，则两种组合是不同的。
#include "algorithm"
#include "functional"
#include "iostream"
#include "unordered_set"
#include "vector"
using namespace std;

/*使用数组hash去重*/
class Solution1 {
public:
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> ret;
    vector<int> combination;
    // 去重
    unordered_set<size_t> existence;
    dfs(candidates, target, ret, combination, 0, existence);

    return ret;
  }
  std::size_t vec_hash(vector<int> const &vec) const {
    std::size_t seed = vec.size();
    for (auto &i : vec) {
      seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
  void dfs(const vector<int> &candidates, const int &target,
           vector<vector<int>> &ret, vector<int> &combination, int sum,
           unordered_set<size_t> &existence) {
    if (sum == target) {
      auto v = combination;
      sort(v.begin(), v.end());
      auto id = vec_hash(v);
      if (existence.count(id) == 0) {
        existence.emplace(id);
        ret.push_back(v);
      }
    } else if (sum > target) {
      return;
    } else {
      for (auto c : candidates) {
        combination.push_back(c);
        dfs(candidates, target, ret, combination, sum + c, existence);
        combination.pop_back();
      }
    }
  }
};

class Solution {
public:
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    vector<vector<int>> ret;
    vector<int> combination;
    sort(candidates.begin(), candidates.end());
    dfs(candidates, 0, target, ret, combination);
    return ret;
  }
  // return refuse?
  bool dfs(const vector<int> &candidates, const int begin, const int &target,
           vector<vector<int>> &ret, vector<int> &combination) {
    if (target == 0) {
      ret.push_back(combination);
      return true;
    } else if (target < 0) {
      return true; 
    } else {
      int idx = begin;
      // 去重，从begin开始
      for (auto c = candidates.begin() + idx; c < candidates.end(); ++c) {
        combination.push_back(*c);
        auto refuse = dfs(candidates, idx++, target - *c, ret, combination);
        combination.pop_back();
        // 剪枝。candidate升序，若c被拒绝（target-*c < 0）则后续更大的c一定会被拒绝
        if(refuse)break;
      }
      return false;
    }
  }
};

int main() {
  Solution s;
  vector<int> candidates = {2, 3, 5};
  int target = 8;
  auto ret = s.combinationSum(candidates, target);
  for (auto arr : ret) {
    cout << endl;
    for (auto x : arr) {
      cout << x << '\t';
    }
  }
}