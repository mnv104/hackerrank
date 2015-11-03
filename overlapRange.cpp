#include <set>
#include <stdexcept>
#include <functional>
#include <iostream>


using namespace std;

std::pair<int, int>
findNewRange(const std::pair<int, int> &p1,
             const std::pair<int, int> &p2)
{
   int newMin = std::min(p1.first, p2.first);
   int newMax = std::max(p1.second, p2.second);
   return std::make_pair(newMin, newMax);
}

bool
isIntersecting(const std::pair<int, int> &p1,
               const std::pair<int, int> &p2)
{
   if (p1.second < p2.first ||
       p2.second < p1.first) {
      return false;
   }
   return true;
}

int
isCovered(const std::pair<int, int> &p1,
          const std::pair<int, int> &p2)
{
   if (p1.first <= p2.first && p1.second >= p2.second) {
      return 1;
   }
   if (p2.first <= p1.first && p2.second >= p1.second) {
      return 2;
   }
   return 0;
}

struct comparator {
   bool operator() (const std::pair<int, int> &p1, const std::pair<int, int> &p2)
   {
      if (p1.second > p2.second) {
         return true;
      }
      return false;
   }
};



std::set<std::pair<int, int>>
findOverlapRange(const std::set<std::pair<int, int>> &sMin,
                 const std::set<std::pair<int, int>, comparator> &sMax,
                 const std::pair<int, int> &range)
{
   std::set<std::pair<int, int>> s1;
   std::pair<int, int> p1, p2;
   int minDiff, maxDiff;
   bool lowValid = false, hiValid = false;
   for (auto i: sMin) {
      if (i.first <= range.first) {
         if (lowValid && range.first - i.first < minDiff) {
            minDiff = range.first - i.first;
            p1 = i;
         } else if (!lowValid) {
            minDiff = range.first - i.first;
            lowValid = true;
            p1 = i;
         }
      }
      if (i.second >= range.second) {
         if (hiValid && i.second - range.second < maxDiff) {
            maxDiff = i.second - range.second;
            p2 = i;
         } else if (!hiValid) {
            maxDiff = i.second - range.second;
            hiValid = true;
            p2 = i;
         }
      }
   }
   if (p1 == p2) {
      s1.insert(p1);
      return s1;
   } else {
      int v;
      v = isCovered(p1, range);
      if (v == 1) {
         s1.insert(p1);
         return s1;
      }
      v = isCovered(p2, range);
      if (v == 1) {
         s1.insert(p2);
         return s1;
      }
      if (isIntersecting(p1, p2)) {
         s1.insert(p1);
         s1.insert(p2);
         return s1;
      }
      std::pair<int, int> newRange = findNewRange(p1, p2);
      s1.insert(p1);
      int newVal = p1.second;
      for (auto i: sMin) {
         if (i != p1) {
            std::pair<int, int> j;
            std::set<std::pair<int, int>, comparator>::const_iterator it = sMax.begin();
            while (it != sMax.end()) {
               j = *it;
               if (j.first <= newVal) {
                  newVal = j.second;
                  s1.insert(j);
                  if (newVal >= newRange.second) {
                     return s1;
                  }
                  break;
               }
               it++;
            }
         }
      }
      throw std::invalid_argument("Not possible");
   }
}

void displayRanges(const std::set<std::pair<int, int>> &sMin,
                   const std::set<std::pair<int, int>, comparator> &sMax,
                   const std::pair<int, int> &p)
{
   cout << p.first << " " << p.second << ":";
   try {
      std::set<std::pair<int, int>> s2;
      s2 = findOverlapRange(sMin, sMax, p);
      for (auto i: s2) {
         cout << i.first << " " << i.second << ", ";
      }
      cout << endl;
   } catch (const std::exception &e) {
      cout << e.what() << endl;
   }

}


int main()
{
   std::set<std::pair<int, int>> sMin;
   std::set<std::pair<int, int>, comparator> sMax;
   std::array<std::pair<int, int>, 9> s1;
   s1[0] = make_pair(1,4);
   s1[1] = make_pair(30, 40);
   s1[2] = make_pair(20, 91);
   s1[3] = make_pair(8, 10);
   s1[4] = make_pair(6, 7);
   s1[5] = make_pair(3, 9);
   s1[6] = make_pair(9, 12);
   s1[7] = make_pair(11, 14);
   s1[8] = make_pair(14, 20);
   for (unsigned int i = 0; i < s1.size(); i++) {
      sMin.insert(s1[i]);
      sMax.insert(s1[i]);
   }
#if 0
   for (auto i: sMin) {
      cout << i.first << " " << i.second << endl;
   }
   cout << endl;
   for (auto i: sMax) {
      cout << i.first << " " << i.second << endl;
   }
   cout << endl;
#endif
   displayRanges(sMin, sMax, make_pair(3, 13));
   displayRanges(sMin, sMax, make_pair(12, 17));
   displayRanges(sMin, sMax, make_pair(1, 14));
   displayRanges(sMin, sMax, make_pair(-4, -1));
   displayRanges(sMin, sMax, make_pair(4, 7));
   displayRanges(sMin, sMax, make_pair(4, 17));
   return 0;
}
