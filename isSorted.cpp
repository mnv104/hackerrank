#include <vector>
using namespace std;


bool isSorted(const std::vector<int> nums)
{
   size_t l = nums.size();
   bool sorted = true, init = false, lt = false;
   for (int i = 1; i < l; i++) {
      bool thisLt;
      thisLt = (nums[i-1] > nums[i]);
      if (!init) {
         init = true;
         lt = thisLt;
      } else if (lt ^ thisLt) {
         sorted = false;
         break;
      }
   }
   return sorted;
}
