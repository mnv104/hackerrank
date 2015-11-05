#include <vector>
#include <map>
#include <stdint.h>
#include <limits.h>
#include <iostream>
#include <algorithm>

using namespace std;
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        vector<vector<int>> v;
        unsigned int l = nums.size();
        map<int, pair<int, int>> m;
        int lastPos = INT_MAX;

        for (int i = 0; i < l; i++) {
            if (nums[i] > 0) {
                break;
            }
            for (int j = i + 1; j < l; j++) {
                int tot = nums[i] + nums[j];
                if (tot > 0) {
                    break;
                }
                m[tot * -1] = make_pair(nums[i], nums[j]);
                if (tot * -1 < lastPos) {
                    lastPos = tot * -1;
                }
            }
        }
        vector<int>::reverse_iterator it = nums.rbegin();
        while (it != nums.rend()) {
            if (*it < lastPos) {
                break;
            }
            try {
                pair<int, int> p;
                p = m.at(*it);
                m.erase(*it);
                vector<int> iv;
                iv.push_back(p.first);
                iv.push_back(p.second);
                iv.push_back(*it);
                v.push_back(iv);
            } catch (const std::exception &e) {
            }
            it++;
        }
        return v;
    }
};

int main(void)
{
   int a[] = {7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6};
   vector<int> v(a, a+sizeof(a)/sizeof(a[0]));
   Solution s;
   vector<vector<int>> v1;
   v1 = s.threeSum(v);
   for (auto i: v1) {
      for (auto j: i) {
         cout << j << " ";
      }
      cout << endl;
   }
   return 0;
}

