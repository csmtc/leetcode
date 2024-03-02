#include <algorithm>
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

// 使用排序树，t= O(nlogn)
class SolutionV1 {
public:
  bool containsNearbyAlmostDuplicate(vector<int> &nums, int indexDiff,
                                     int valueDiff) {
    set<int> nset; // 排序树
    int left = 0, right = 1;
    nset.emplace(nums[0]);
    while (right < nums.size()) {
      auto val = nums[right];
      auto found = nset.lower_bound(val - valueDiff);

      if (found != nset.end() && abs(*found - val) <= valueDiff) {
        return true;
      }
      ++right, nset.emplace(val);
      if (right > indexDiff) {
        nset.erase(nums[left]), ++left;
      }
    }
    return false;
  }
};
class Solution {
public:
  int inline barrelID(const int &x, const int &barrelSize) {
    return x >= 0 ? x / barrelSize : (x + 1) / barrelSize - 1;
  }
  bool containsNearbyAlmostDuplicate(vector<int> &nums, int indexDiff,
                                     int valueDiff) {
    unordered_map<int, int> barrels; // <桶ID,<桶中最小元素,桶中最大元素>>
    int left = 0, right = 1;
    const int barrelSize = valueDiff + 1;
    barrels[barrelID(nums[0], barrelSize)] = nums[0];
    while (right < nums.size()) {
      int val = nums[right];
      auto id = barrelID(val, barrelSize);
      unordered_map<int, int>::iterator found;
      if (barrels.count(id)) {
        return true;
      } else if (barrels.count(id - 1) && val - barrels[id - 1] <= valueDiff)
        return true;
      else if (barrels.count(id + 1) && barrels[id + 1] - val <= valueDiff)
        return true;

      ++right, barrels[id] = val;
      if (right > indexDiff) {
        barrels.erase(barrelID(nums[left], barrelSize)), ++left;
      }
    }
    return false;
  }
};

inline void go() {
  Solution s;
  vector<int> nums{1, 2, 3, 1};
  cout << s.containsNearbyAlmostDuplicate(nums, 3, 0);
}
int main() {
  clock_t begin = clock();
  go();
  clock_t end = clock();
  cout << endl << "exec cost " << (end - begin) << " us.";
}