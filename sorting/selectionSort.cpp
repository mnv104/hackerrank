#include "sort.hpp"

void SelectionSortAlgo::sort(std::vector<int> &v)
{
   for (unsigned int i = 0; i < v.size(); i++) {
      int k = i;
      for (unsigned int j = i + 1; j < v.size(); j++) {
         if (v[j] < v[k]) {
            k = j;
         }
      }
      if (k != i) {
         int temp = v[i];
         v[i] = v[k];
         v[k] = temp;
      }
   }
}
