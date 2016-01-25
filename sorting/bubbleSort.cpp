#include "sort.hpp"

void BubbleSortAlgo::sort(std::vector<int> &v)
{
   for (unsigned int i = 0; i < v.size(); i++) {
      for (unsigned int j = 0; j < v.size() - 1; j++) {
         if (v[j] > v[j+1]) {
            int temp = v[j];
            v[j] = v[j+1];
            v[j+1] = temp;
         }
      }
   }
   return;
}
