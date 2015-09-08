#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>
#include <getopt.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void display(const std::string &s, const std::vector<int> &v)
{
   cout << s << endl;
   for (auto i: v) {
      cout << i << " ";
   }
   cout << endl;
}

bool isAscending(const std::vector<int> nums)
{
   size_t l = nums.size();
   return nums[0] < nums[l-1];
}


double medianOfArray(const std::vector<int> &v)
{
   size_t l = v.size();
   if (l % 2 == 0) {
      return (v[l/2] + v[l/2-1]) / 2.0;
   } else {
      return v[l/2];
   }
}


/*
 * O(M+N) time complexity
 */
double median1(const std::vector<int> &v1,
           const std::vector<int> &v2)
{
   int hand1, hand2;
   size_t l1 = v1.size(), l2 = v2.size();
   if (l1 == 0) {
      return medianOfArray(v2);
   } else if (l2 == 0) {
      return medianOfArray(v1);
   }
   bool v1ascending = isAscending(v1),
        v2ascending = isAscending(v2);
   hand1 = v1ascending ? 0 : l1-1;
   hand2 = v2ascending ? 0 : l2-1;
   std::vector<int> middle;
   if ((l1 + l2) % 2 == 0) {
      middle.push_back((l1 + l2) / 2 - 1);
   }
   middle.push_back((l1 + l2) / 2);
   int count = 0;
   std::vector<int> sortedVec;
   while (1) {
      if (hand1 >= 0 && hand1 < l1 && hand2 >= 0 && hand2 < l2) {
         if (v1[hand1] < v2[hand2]) {
            sortedVec.push_back(v1[hand1]);
            count++;
            v1ascending ? hand1++ : hand1--;
         } else if (v1[hand1] == v2[hand2]) {
            sortedVec.push_back(v1[hand1]);
            sortedVec.push_back(v2[hand2]);
            count += 2;
            v1ascending ? hand1++ : hand1--;
            v2ascending ? hand2++ : hand2--;
         } else {
            sortedVec.push_back(v2[hand2]);
            count++;
            v2ascending ? hand2++ : hand2--;
         }
      } else if (hand1 >= 0 && hand1 < l1) {
         sortedVec.push_back(v1[hand1]);
         count++;
         v1ascending ? hand1++ : hand1--;
      } else if (hand2 >= 0 && hand2 < l2) {
         sortedVec.push_back(v2[hand2]);
         count++;
         v2ascending ? hand2++ : hand2--;
      } else {
         break;
      }
   }
   double med = 0.0;
   size_t m = middle.size();
   while (!middle.empty()) {
      int f = middle.front();
      middle.erase(middle.begin());
      med += sortedVec[f];
   }
   return med / m;
}

int main(int argc, char *argv[])
{
   int c;
   vector<int> v1, v2;

   while ((c = getopt(argc, argv, "a:b:")) != EOF) {
      switch (c) {
         case 'a':
            {
            int f;
            stringstream ss;
            ss << optarg;
            while (ss >> f) {
               v1.push_back(f);
            }
            break;
            }
         case 'b':
            {
            int f;
            stringstream ss;
            ss << optarg;
            while (ss >> f) {
               v2.push_back(f);
            }
            break;
            }
         default:
            exit(1);
      }
   }
   cout << "Median = " << median1(v1, v2) << endl;
   return 0;
}
