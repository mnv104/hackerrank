#include <vector>
#include <stdexcept>
#include <iostream>

using namespace std;

std::vector<int> findContigTargetSum(const std::vector<int> &v,
                                     int target)
{
   std::vector<int> v1;
   size_t l = v.size();
   int sum = 0, j = -1;
   for (unsigned int i = 0; i < l; i++) {
      sum += v[i];
      if (sum > target) {
         if (j != -1) {
            while (sum > target) {
               sum -= v[j];
               j++;
            }
            if (sum == target) {
               v1.reserve(i - j + 1);
               std::copy(v.begin() + j, v.begin() + i + 1, back_inserter(v1));
               return v1;
            }
         } else {
            sum = 0;
         }
      } else if (sum < target) {
         if (j == -1) {
            j = i;
         }
      } else {
         v1.reserve(i - j + 1);
         std::copy(v.begin() + j, v.begin() + i + 1, back_inserter(v1));
         return v1;
      }
   }
   throw std::invalid_argument("No such subset");
}

void displaySubset(const std::vector<int> &v,
                   int targetNumber)
{
   cout << "Target number " << targetNumber << ":";
   try {
      std::vector<int> v1 = findContigTargetSum(v, targetNumber);
      for (auto i: v1) {
         cout << i << " ";
      }
      cout << endl;
   } catch (const std::exception &e) {
      cout << "No such subset" << endl;
   }
}

int main()
{
   int a[] = {1, 3, 5, 7, 9};
   std::vector<int> v(a, a+sizeof(a)/sizeof(a[0]));
   displaySubset(v, 4);
   displaySubset(v, 12);
   displaySubset(v, 15);
   return 0;
}
