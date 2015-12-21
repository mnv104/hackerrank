#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>
#include <stdint.h>
#include <sys/types.h>

using namespace std;

class BitVector {
   unsigned long *v;
   int max;
   uint32_t numberOfLongs;
   static const uint32_t bits_per_long;
public:
   BitVector(int number): max(number) {
      numberOfLongs = (number - 1)/ bits_per_long + 1;
      v = new unsigned long[numberOfLongs];
      for (unsigned int i = 0; i < numberOfLongs; i++) {
         v[i] = 0;
      }
   }
   ~BitVector() {
      delete [] v;
   }
   void setBit(int pos) {
      if (pos > max) {
         throw std::out_of_range("Invalid index");
      }
      int id = pos / bits_per_long;
      long mask = 1UL << (pos % bits_per_long);
      v[id] |= mask;
   }
   bool testBit(int pos) {
      if (pos > max) {
         throw std::out_of_range("Invalid index");
      }
      int id = pos / bits_per_long;
      long mask = 1UL << (pos % bits_per_long);
      return ((v[id] & mask) != 0);
   }
   void clearBit(int pos) {
      if (pos > max) {
         throw std::out_of_range("Invalid index");
      }
      int id = pos / bits_per_long;
      long mask = 1UL << (pos % bits_per_long);
      v[id] &= ~mask;
   }
   void toggleBit(int pos) {
      if (pos > max) {
         throw std::out_of_range("Invalid index");
      }
      int id = pos / bits_per_long;
      long mask = 1UL << (pos % bits_per_long);
      v[id] ^= mask;
   }
   uint32_t countSetBits() {
      uint32_t total = 0;
      for (unsigned int i = 0; i < numberOfLongs; i++) {
         unsigned long m = v[i];
         int count = 0;
         while (m > 0) {
            m = m & (m - 1);
            count++;
         }
         total += count;
      }
      return total;
   }
};

const uint32_t BitVector::bits_per_long = sizeof(unsigned long) * 8;


int main()
{
   const uint32_t n = 32;
   BitVector v(n);
   uint32_t count = 0;
   srand(time(NULL));
   std::vector<int> v1, v2;
   for (int i = 0; i < n; i++) {
      if (rand() % 2) {
         v.setBit(i);
         v1.push_back(i);
         count++;
      }
   }
   for (auto i: v1) {
      //cout << "Bit  " << i << ":" << v.testBit(i) << endl;
      assert(v.testBit(i) == true);
      if (rand() % 2) {
         v2.push_back(i);
         v.clearBit(i);
         count--;
      } else {
         v.toggleBit(i);
         count--;
      }
   }
   for (auto i: v2) {
      //cout << "Bit  " << i << ":" << v.testBit(i) << endl;
      assert(v.testBit(i) == false);
      v.toggleBit(i);
      count++;
   }
   for (auto i: v1) {
      vector<int>::iterator it;
      it = find(v2.begin(), v2.end(), i);
      if (it != v2.end()) {
         assert(v.testBit(i) == true);
      } else {
         assert(v.testBit(i) == false);
      }
   }
   cout << "Number of bits set: " << v.countSetBits() << " should be " << count << endl;
   assert(count == v.countSetBits());
   return 0;
}
