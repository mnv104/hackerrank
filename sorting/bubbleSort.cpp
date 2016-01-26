#include "sort.hpp"

void BubbleSortAlgo::sort(std::vector<int> &v)
{
   for (unsigned int i = 1; i < v.size(); i++) {
      bool swapped = false;
      for (unsigned int j = v.size() - 1; j >= i; j--) {
         if (v[j] < v[j-1]) {
            int temp = v[j];
            v[j] = v[j-1];
            v[j-1] = temp;
            swapped = true;
         }
      }
      if (!swapped) {
         break;
      }
   }
   return;
}
