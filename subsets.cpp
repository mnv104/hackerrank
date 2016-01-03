#include <set>
#include <iostream>

using namespace std;


template <typename T>
set<set<T>>
findSubsets(const set<T> &s)
{
   set<set<T>> us;
   if (s.size() == 0) {
      us.insert(s);
      return us;
   } else {
      set<T> t = s;
      T f = *(t.begin());
      t.erase(f);
      set<set<T>> us1;
      us = findSubsets(t);
      for (auto e: us) {
         set<T> t1 = e;
         t1.insert(f);
         us1.insert(t1);
      }
      us.insert(us1.begin(), us1.end());
      return us;
   }
}

template<typename T>
set<T>
makeSet(int number, const set<T> &s)
{
   set<T> s1;
   typename set<T>::iterator it = s.begin();
   for (; number; number >>= 1) {
      if (number & 0x1) {
         s1.insert(*it);
      }
      it++;
   }
   return s1;
}


template <typename T>
set<set<T>>
findSubsets2(const set<T> &s)
{
   set<set<T>> us;
   size_t l = s.size();
   size_t numSubsets = 1 << l;
   for (unsigned int i = 0; i < numSubsets; i++) {
      set<T> t = makeSet(i, s);
      us.insert(t);
   }
   return us;
}

template <typename T>
void
display(const set<set<T>> &us)
{
   for (auto e: us) {
      for (auto f: e) {
         cout << f << " ";
      }
      cout << endl;
   }
   return;
}

int main(void)
{
   set<int> s;
   s.insert(1);
   s.insert(2);
   s.insert(3);
   s.insert(4);

   cout << "Subsets using recursion" << endl;
   set<set<int>> us = findSubsets(s);
   display(us);
   cout << "Subsets using combinatorics " << endl;
   set<set<int>> us2 = findSubsets2(s);
   display(us2);
   return 0;
}
