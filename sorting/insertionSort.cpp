#include "sort.hpp"

void InsertionSortAlgo::sort(std::vector<int> &v)
{
   for (unsigned int i = 1; i < v.size(); i++) {
      int k = i;
      while (k > 0 && v[k] < v[k-1]) {
         int temp = v[k-1];
         v[k-1] = v[k];
         v[k] = temp;
         k--;
      }
   }
}
