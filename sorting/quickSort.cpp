#include "sort.hpp"
#include <iostream>

unsigned int QuickSortAlgo::partition(std::vector<int> &v,
                              unsigned int      low,
                              unsigned int      high)
{
   int pivot;
   pivot = v[high];
   unsigned int i = low;
   for (unsigned int j = low; j < high; j++) {
      if (v[j] <= pivot) {
         int temp = v[i];
         v[i] = v[j];
         v[j] = temp;
         i++;
      }
   }
   int temp = v[i];
   v[i] = pivot;
   v[high] = temp;
   return i;
}

void QuickSortAlgo::sortInt(std::vector<int> &v,
                            unsigned int      low,
                            unsigned int      high)
{
   if (low >= high) {
      return;
   }
   unsigned int pivotIndex = partition(v, low, high);
   sortInt(v, low, pivotIndex-1);
   sortInt(v, pivotIndex+1, high);
}

void QuickSortAlgo::sort(std::vector<int> &v)
{
   unsigned int l = v.size();
   sortInt(v, 0, l-1);
}
