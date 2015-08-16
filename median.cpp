#include <stdio.h>
#include <vector>
#include <queue>
#include <functional>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Median {
public:
   std::priority_queue<int> maxHeap1;
   std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap2;
   void insert(int value);
   double getMedian(void);
};

void Median::insert(int value)
{
   size_t l = maxHeap1.size();
   size_t m = minHeap2.size();
   if (l - m == 0) {
      if (l != 0 && value > maxHeap1.top()) {
         minHeap2.push(value);
      } else {
         maxHeap1.push(value);
      }
   } else if (labs(l - m) == 1) {
      if (l > m) {
         if (maxHeap1.top() > value) {
            int r = maxHeap1.top();
            maxHeap1.pop();
            minHeap2.push(r);
            maxHeap1.push(value);
         } else {
            minHeap2.push(value);
         }
      } else {
         if (minHeap2.top() < value) {
            int r = minHeap2.top();
            minHeap2.pop();
            maxHeap1.push(r);
            minHeap2.push(value);
         } else {
            maxHeap1.push(value);
         }
      }
   }
}


double Median::getMedian(void)
{
   size_t l = maxHeap1.size();
   size_t m = minHeap2.size();
   if (l == 0 && m == 0) {
      throw std::invalid_argument("No elements inserted yet");
   }
   if (l - m == 0) {
      return (maxHeap1.top() + minHeap2.top()) / 2.0;
   } else {
      if (l > m) {
         return maxHeap1.top();
      } else {
         return minHeap2.top();
      }
   }
}


int main(void)
{
   Median m;
   cout << "Please enter values " <<endl;
   while (!cin.eof()) {
      int value;
      cin >> value;
      m.insert(value);
      cout << "New median is " << m.getMedian() << endl;
   }
   return 0;
}
