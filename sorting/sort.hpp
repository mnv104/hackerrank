#ifndef _SORT_HPP
#define _SORT_HPP

#include <vector>
#include <stdexcept>
#include <exception>

enum SortAlgoTypes {
   BUBBLE_SORT,
   INSERTION_SORT,
   SELECTION_SORT,
   MERGE_SORT,
   QUICK_SORT,
   SENTINEL_SORT
};

class SortAlgo {
public:
   std::string name;
   SortAlgo(const std::string &_name) :name(_name) { }
   virtual ~SortAlgo() { }
   virtual void sort(std::vector<int> &v) = 0;
};

class BubbleSortAlgo : public SortAlgo {
public:
   BubbleSortAlgo(): SortAlgo("bubble sort") { }
   virtual ~BubbleSortAlgo() { }
   void sort(std::vector<int> &v);
};

class InsertionSortAlgo : public SortAlgo {
public:
   InsertionSortAlgo(): SortAlgo("insertion sort") { }
   virtual ~InsertionSortAlgo() { }
   void sort(std::vector<int> &v);
};

class SelectionSortAlgo : public SortAlgo {
public:
   SelectionSortAlgo(): SortAlgo("selection sort") { }
   virtual ~SelectionSortAlgo() { }
   void sort(std::vector<int> &v);
};

class MergeSortAlgo : public SortAlgo {
   void sortInt(std::vector<int> &v, unsigned int begin, unsigned int end);
public:
   MergeSortAlgo(): SortAlgo("merge sort") { }
   virtual ~MergeSortAlgo() { }
   void sort(std::vector<int> &v);
};

class QuickSortAlgo : public SortAlgo {
   unsigned int partition(std::vector<int> &v, unsigned int low, unsigned int high);
   void sortInt(std::vector<int> &v, unsigned int low, unsigned int high);
public:
   QuickSortAlgo(): SortAlgo("quick sort") { }
   virtual ~QuickSortAlgo() { }
   void sort(std::vector<int> &v);
};


class SortFactory {
public:
   static SortAlgo *create(SortAlgoTypes type) {
      if (type == BUBBLE_SORT) {
         return new BubbleSortAlgo();
      } else if (type == INSERTION_SORT) {
         return new InsertionSortAlgo();
      } else if (type == SELECTION_SORT) {
         return new SelectionSortAlgo();
      } else if (type == MERGE_SORT) {
         return new MergeSortAlgo();
      } else if (type == QUICK_SORT) {
         return new QuickSortAlgo();
      } else {
         throw std::invalid_argument("Bad sort algorithm type");
      }
   }
};

#endif
