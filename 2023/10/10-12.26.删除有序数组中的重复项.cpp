// 给你一个 非严格递增排列 的数组 nums ，请你 原地
// 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。元素的
// 相对顺序 应该保持 一致 。然后返回 nums 中唯一元素的个数。
#include <algorithm>
#include <iostream>

#include "vector"
using namespace std;

//集中删除
class Solution1 {
 public:
  int removeDuplicates(vector<int> &nums) {
    int sum_rmcnt = 0, n = nums.size();
    for (int i = 0, offset; i < n;) {
      for (offset = 1; offset < n - i && nums[i] == nums[i + offset]; ++offset)
        ;
      if (--offset > 0) {
        for (auto j = i + offset; j < n; ++j) {
          nums[j - offset] = nums[j];
        }
        n -= offset;
        sum_rmcnt += offset;
      }
      ++i;
    }
    n = nums.size();
    // for (int i = 0; i < sum_rmcnt; ++i) {
    //   nums.pop_back();
    // }
    return n - sum_rmcnt;
  }
};

// 迭代时删除
class Solution2{
 public:
  int removeDuplicates(vector<int> &nums) {
    int valid = nums.size(), val;
    for (auto x = nums.begin(); x != nums.end(); ++x) {
      val = *x;
      while(x+1<nums.end() && *(x+1)==val){
        nums.erase(x);
        --valid;
      }
    }
    return valid;
  }
};

// 双指针
class Solution {
 public:
  int removeDuplicates(vector<int> &nums) {
    int valid=1,n = nums.size();
    for (int p =0,q=p+1;q!=n;) {
      if (nums[p] == nums[q]) {
        ++q;
      } else {
        nums[++p] = nums[q];
        ++valid;
      }
    }
    return valid;
  }
};

int main() {
  vector<int> nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};  // 输入数组
  int n = Solution().removeDuplicates(nums);
  cout << n << endl;
  for (auto x : nums) {
    cout << x << '\t';
  }
}