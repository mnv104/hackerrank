#include "sort.hpp"
#include <iostream>


void MergeSortAlgo::sortInt(std::vector<int> &v,
                            unsigned int      begin,
                            unsigned int      end)
{
   if (begin >= end) {
      return;
   }
   unsigned int middle = (begin + end) / 2;
   sortInt(v, begin, middle);
   sortInt(v, middle + 1, end);
   std::vector<int> copyV(v.begin(), v.begin() + middle + 1);
   unsigned int hand1 = begin, hand2 = middle + 1;
   unsigned int k = begin;
   while (hand1 <= middle && hand2 <= end) {
      v[k++] = (copyV[hand1] < v[hand2]) ? copyV[hand1++] : v[hand2++];
   }
   while (hand1 <= middle) {
      v[k++] = copyV[hand1++];
   }
}

void MergeSortAlgo::sort(std::vector<int> &v)
{
   unsigned int l = v.size();
   if (l < 2) {
      return;
   }
   sortInt(v, 0, l-1);
}
