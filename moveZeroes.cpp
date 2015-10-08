#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void findNextNonZero(vector<int> & nums, int &index) {
        int j = index;
        int l = nums.size();
        while (j < l) {
            if (nums[j] != 0) {
                index = j;
                return;
            }
            j++;
        }
        index = -1;
        return;
    }

    void moveZeroes(vector<int>& nums) {
        size_t l = nums.size();
        int i;
        int j = -1;
        for (i = 0; i < l; i++) {
            if (nums[i] == 0) {
                j = (j == -1) ? i + 1: j;
                findNextNonZero(nums, j);
                if (j == -1) {
                    return;
                }
                cout << i << " " << j << endl;
                nums[i] = nums[j];
                nums[j] = 0;
                j += 1;
            }
        }
    }
};

int main()
{
   int a[] = {4,2,4,0,0,3,0,5,1,0};
   std::vector<int> v(a, a + sizeof(a)/sizeof(a[0]));
   Solution s;
   s.moveZeroes(v);
   for (auto i: v) {
      cout << i << " ";
   }
   cout << endl;
   return 0;
}
