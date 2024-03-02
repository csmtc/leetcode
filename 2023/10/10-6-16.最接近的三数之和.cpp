
#include <utility>

#include "algorithm"
#include "iostream"
#include "vector"
using namespace std;

#define CRA_DEBUG

// 给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums
// 中选出三个整数，使它们的和与 target 最接近。 返回这三个数的和。
// 假定每组输入只存在恰好一个解。
const int CRA_INFINITY = 1 << 30;
class Solution {
 public:
  int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
#ifdef CRA_DEBUG
    for (auto x = nums.begin(); x != nums.end(); ++x) cout << *x << '\t';
    cout << endl;
#endif
    int sum, ret, dst, mindistance = CRA_INFINITY;
    // int *p, *q, *r,*data=nums.data();
    auto endp = nums.end() - 2, endq = nums.end() - 1;
    for (auto p = nums.begin(); p != endp; ++p) {
      auto r = nums.end() - 1;
      for (auto q = p + 1; q != endq; ++q) {
        // ++r;
        while (r > q) {
          sum = *p + *q + *r;
          dst = abs(sum - target);
#ifdef CRA_DEBUG
          cout << dst << ':' << *p << '\t' << *q << '\t' << *r << endl;
#endif
          if (dst < mindistance) {
            mindistance = dst;
            ret = sum;
          }
          if (sum - target > 0) {
            --r;
          } else if (sum - target == 0) {
            return sum;
          } else {
            break;
          }
        }
      }
      if (*p + *(p+1) + *(p+2) - target > 0) break;
    }
    return ret;
  }
};

int main() {
  pair<vector<int>, int> input ={{-1,2,1,-4},1};
    //   {
    //   {13,   252,  -87,  -431, -148, 387,  -290, 572,  -311, -721, 222,  673,
    //    538,  919,  483,  -128, -518, 7,    -36,  -840, 233,  -184, -541, 522,
    //    -162, 127,  -935, -397, 761,  903,  -217, 543,  906,  -503, -826, -342,
    //    599,  -726, 960,  -235, 436,  -91,  -511, -793, -658, -143, -524, -609,
    //    -728, -734, 273,  -19,  -10,  630,  -294, -453, 149,  -581, -405, 984,
    //    154,  -968, 623,  -631, 384,  -825, 308,  779,  -7,   617,  221,  394,
    //    151,  -282, 472,  332,  -5,   -509, 611,  -116, 113,  672,  -497, -182,
    //    307,  -592, 925,  766,  -62,  237,  -8,   789,  318,  -314, -792, -632,
    //    -781, 375,  939,  -304, -149, 544,  -742, 663,  484,  802,  616,  501,
    //    -269, -458, -763, -950, -390, -816, 683,  -219, 381,  478,  -129, 602,
    //    -931, 128,  502,  508,  -565, -243, -695, -943, -987, -692, 346,  -13,
    //    -225, -740, -441, -112, 658,  855,  -531, 542,  839,  795,  -664, 404,
    //    -844, -164, -709, 167,  953,  -941, -848, 211,  -75,  792,  -208, 569,
    //    -647, -714, -76,  -603, -852, -665, -897, -627, 123,  -177, -35,  -519,
    //    -241, -711, -74,  420,  -2,   -101, 715,  708,  256,  -307, 466,  -602,
    //    -636, 990,  857,  70,   590,  -4,   610,  -151, 196,  -981, 385,  -689,
    //    -617, 827,  360,  -959, -289, 620,  933,  -522, 597,  -667, -882, 524,
    //    181,  -854, 275,  -600, 453,  -942, 134},
    //   -2805};
  Solution s;
  int dst = s.threeSumClosest(input.first, input.second);
  cout << endl << dst;
  return 0;
}