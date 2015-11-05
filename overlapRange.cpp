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
               const std::pair<int, int> &p2,
               int &length)
{
   if (p1.second < p2.first ||
       p2.second < p1.first) {
      return false;
   }
   if (p1.first <= p2.first) {
      length = std::min(p2.second - p2.first,
                        p1.second - p2.first);
   } else {
      length = std::min(p1.second - p1.first,
                        p2.second - p1.first);
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

struct comparator2 {
   bool operator() (const std::pair<std::pair<int, int>, int> &p1,
                    const std::pair<std::pair<int, int>, int> &p2)
   {
      if (p1.second == p2.second) {
         if (p1.first.first < p2.first.first) {
            return true;
         }
         return p1.first.second < p2.first.second;
      }
      return p1.second > p2.second;
   }
};


std::set<std::pair<int, int>>
findOverlapRange2(const std::set<std::pair<int, int>> &sMin,
                  const std::pair<int, int> &range)
{
   std::set<std::pair<int, int>> s1;
   std::set<std::pair<std::pair<int, int>, int>, comparator2> sMax;
   for (auto i: sMin) {
      int l;
      if (isIntersecting(i, range, l)) {
         //cout << "Adding " << i.first << " " << i.second << "(" << l << "),";
         sMax.insert(make_pair(i, l));
      }
   }
   std::pair<int, int> r;
   bool valid = false;
   bool clampLeft = false, clampRight = false;
   int count = 0;
repeat:
   for (auto i: sMax) {
      //cout << "Getting " << i.first.first << " " << i.first.second << "(" << i.second << "),";
      if (!valid) {
         r = i.first;
         valid = true;
      } else {
         if (isCovered(r, i.first) == 1) {
            continue;
         }
         int l;
         if (!isIntersecting(r, i.first, l)) {
            continue;
         }
         if (clampLeft) {
            if (i.first.first <= r.first) {
               continue;
            }
         }
         if (clampRight) {
            if (i.second >= r.second) {
               continue;
            }
         }
         r = findNewRange(r, i.first);
      }
      s1.insert(i.first);
      if (!clampLeft && r.first <= range.first) {
         clampLeft = true;
      }
      if (!clampRight && r.second >= range.second) {
         clampRight = true;
      }
      if (clampLeft && clampRight) {
         return s1;
      }
   }
   count++;
   if (count == 1) {
      goto repeat;
   }
   throw std::invalid_argument("Not possible");
}


void displayRanges2(const std::set<std::pair<int, int>> &sMin,
                   const std::pair<int, int> &p)
{
   cout << p.first << " " << p.second << ":";
   try {
      std::set<std::pair<int, int>> s2;
      s2 = findOverlapRange2(sMin, p);
      for (auto i: s2) {
         cout << i.first << " " << i.second << ", ";
      }
      cout << endl;
   } catch (const std::exception &e) {
      cout << e.what() << endl;
   }

}

int func()
{
   std::set<std::pair<int, int>> sMin;
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
   }
   displayRanges2(sMin, make_pair(1, 14));
   displayRanges2(sMin, make_pair(3, 13));
   displayRanges2(sMin, make_pair(12, 17));
   displayRanges2(sMin, make_pair(-4, -1));
   displayRanges2(sMin, make_pair(4, 7));
   displayRanges2(sMin, make_pair(4, 17));
   return 0;
}


int func2()
{
   cout << "New Problem" << endl;
   std::set<std::pair<int, int>> sMin;
   std::array<std::pair<int, int>, 5> s1;
   s1[0] = make_pair(1,10);
   s1[1] = make_pair(2, 5);
   s1[2] = make_pair(10, 13);
   s1[3] = make_pair(7, 14);
   s1[4] = make_pair(-5, 1);
   for (unsigned int i = 0; i < s1.size(); i++) {
      sMin.insert(s1[i]);
   }
   displayRanges2(sMin, make_pair(3, 13));
   displayRanges2(sMin, make_pair(-3, 13));
   return 0;
}

int func3()
{
   cout << "New Problem2" << endl;
   std::set<std::pair<int, int>> sMin;
   std::array<std::pair<int, int>, 3> s1;
   s1[0] = make_pair(3, 8);
   s1[1] = make_pair(9, 13);
   s1[2] = make_pair(7, 10);
   for (unsigned int i = 0; i < s1.size(); i++) {
      sMin.insert(s1[i]);
   }
   displayRanges2(sMin, make_pair(3, 13));
   return 0;
}

int func4()
{
   cout << "New Problem2" << endl;
   std::set<std::pair<int, int>> sMin;
   std::array<std::pair<int, int>, 3> s1;
   s1[0] = make_pair(4, 10);
   s1[1] = make_pair(8, 14);
   s1[2] = make_pair(10, 16);
   for (unsigned int i = 0; i < s1.size(); i++) {
      sMin.insert(s1[i]);
   }
   displayRanges2(sMin, make_pair(5, 15));
   return 0;
}

int main()
{
   func();
   func2();
   func3();
   func4();
}
