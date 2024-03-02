
#include "vector"
#include <algorithm>
#include <iostream>
using namespace std;

// 可能溢出
class SolutionV1 {
public:
  vector<vector<int>> fourSum(vector<int> &nums, int target) {
    int i, j, k, l, n = nums.size(), sum_target;
    vector<vector<int>> ret;
    sort(nums.begin(), nums.end());
    for (i = 0; i < n - 3; ++i) {
      if (i > 0 && nums[i] == nums[i - 1])
        continue;
      for (j = i + 1; j < n - 2; ++j) {
        if (j > i + 1 && nums[j] == nums[j - 1])
          continue;
        sum_target = target - nums[i] - nums[j];
        for (k = j + 1, l = n - 1; k < n - 1; ++k) {
          if (k > j + 1 && nums[k] == nums[k - 1])
            continue;
          for (; k < l && nums[k] + nums[l] > sum_target; --l)
            ;
          if (k >= l)
            break;
          if (nums[k] + nums[l] == sum_target)
            ret.push_back({nums[i], nums[j], nums[k], nums[l]});
        }
      }
    }
    return ret;
  }
};


class Solution {
public:
  vector<vector<int>> fourSum(vector<int> &nums, int target) {
    int i, j, k, l, n = nums.size();
    long sum_target;
    vector<vector<int>> ret;
    sort(nums.begin(), nums.end());
    for (i = 0; i < n - 3; ++i) {
      if (i > 0 && nums[i] == nums[i - 1])
        continue;
      for (j = i + 1; j < n - 2; ++j) {
        if (j > i + 1 && nums[j] == nums[j - 1])
          continue;
        sum_target = (long)target -nums[i] - nums[j];
        for (k = j + 1, l = n - 1; k < n - 1; ++k) {
          if (k > j + 1 && nums[k] == nums[k - 1])
            continue;
          for (; k < l && nums[k] + nums[l] > sum_target; --l)
            ;
          if (k >= l)
            break;
          if (nums[k] + nums[l] == sum_target)
            ret.push_back({nums[i], nums[j], nums[k], nums[l]});
        }
      }
    }
    return ret;
  }
};

int main() {
  vector<int> arr = {1,0,-1,0,-2,2};
  Solution s;
  vector<vector<int>> dst = s.fourSum(arr, 0);
  for (auto p : dst) {
    for (auto x : p) {
      cout << '\t' << x << "\t";
    }
    cout << endl;
  }
  return 0;
}