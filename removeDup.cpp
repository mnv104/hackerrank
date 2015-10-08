#include <map>
#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;


class Solution {
public:
    bool isPresent(const std::map<int, bool> &m, int number) {
        try {
            return m.at(number);
        } catch (const std::out_of_range &e) {
            return false;
        }
    }

    void replace(vector<int>& nums,
                 map<int, bool> &m,
                 int &begin, int &end)
    {
       while (end >= begin) {
          if (isPresent(m, nums[end])) {
             nums.resize(nums.size() - 1);
             end--;
             continue;
          }
          nums[begin] = nums[end];
          end--;
          nums.resize(nums.size() - 1);
          break;
       }
       return;
    }

    int removeGeneric(vector<int>& nums,
                      map<int, bool> &m) {
        bool specific = m.size() > 0;
        int begin = 0, end = nums.size() - 1;
        while (begin <= end) {
           if (isPresent(m, nums[begin])) {
              replace(nums, m, begin, end);
           }
           if (!specific) {
              m[nums[begin]] = true;
           }
           begin++;
        }
        return nums.size();
    }

    int removeSpecificDup(vector<int>& nums, int val) {
        std::map<int, bool> m;
        m[val] = true;
        return removeGeneric(nums, m);
    }

    int removeDup(vector<int>& nums) {
        std::map<int, bool> m;
        return removeGeneric(nums, m);
    }

};


int main(void)
{
   int a[] = {2, 3, 3, 4, 5, 9, 10, 10, 11, 3};
   int b[] = {2, 3, 3};
   std::vector<int> v(a, a + sizeof(a)/ sizeof(a[0]));
   std::vector<int> v1(b, b + sizeof(b)/ sizeof(b[0]));
   Solution s;
   cout << s.removeSpecificDup(v, 3) << endl;
   for (auto i: v) {
      cout << i << " ";
   }
   cout << endl;

   cout << s.removeDup(v) << endl;
   for (auto i: v) {
      cout << i << " ";
   }
   cout << endl;
   cout << s.removeSpecificDup(v1, 3) << endl;
   for (auto i: v1) {
      cout << i << " ";
   }
   return 0;
}
