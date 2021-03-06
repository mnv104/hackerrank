#include <iostream>
#include <vector>
#include "sort.hpp"

using namespace std;

int main()
{
   int vInt[] = {8, 2, 4, 12, 6, 10, 11, 20, 19, 15, 17};
   cout << "Input array " << endl;
   for (auto e: vInt) {
      cout << e << " ";
   }
   cout << endl;
   SortAlgoTypes algos[] = {BUBBLE_SORT, INSERTION_SORT, SELECTION_SORT, MERGE_SORT, QUICK_SORT};
   for (unsigned int i = 0; i < sizeof(algos)/sizeof(algos[0]); i++) {
      vector<int> v(vInt, vInt + sizeof(vInt)/sizeof(vInt[0]));

      SortAlgo *s = SortFactory::create(algos[i]);
      s->sort(v);
      cout << "Sorted array using " << s->name << endl;
      for (auto e: v) {
         cout << e << " ";
      }
      cout << endl;
      delete s;
   }
   return 0;
}
