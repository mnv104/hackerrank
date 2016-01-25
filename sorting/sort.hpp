#ifndef _SORT_HPP
#define _SORT_HPP

#include <vector>
#include <stdexcept>
#include <exception>

enum SortAlgoTypes {
   BUBBLE_SORT,
   INSERTION_SORT,
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

class SortFactory {
public:
   static SortAlgo *create(SortAlgoTypes type) {
      if (type == BUBBLE_SORT) {
         return new BubbleSortAlgo();
      } else if (type == INSERTION_SORT) {
         return new InsertionSortAlgo();
      } else {
         throw std::invalid_argument("Bad sort algorithm type");
      }
   }
};

#endif
