#include <vector>
#include <assert.h>
#include <stdexcept>
#include <iostream>

using namespace std;
template<typename T>
class Number {
public:
   T _value;
   T _threshold1;
   T _threshold2;
public:
   Number(T value, T lowThreshold, T mediumThreshold) :
      _value(value), _threshold1(lowThreshold), _threshold2(mediumThreshold) {
         if (_threshold1 > _threshold2) {
            throw std::invalid_argument("Invalid thresholds");
         }
   }
   Number(const Number<T> &num1) {
      _value = num1._value;
      _threshold1 = num1._threshold1;
      _threshold2 = num1._threshold2;
   }

   bool isLow() {
      return _value < _threshold1;
   }
   bool isMedium() {
      return _value >= _threshold1 &&
             _value < _threshold2;
   }
   bool isHigh() {
      return _value >= _threshold2;
   }
   void swap(Number<T> &num1) {
      T temp = num1._value;
      num1._value = _value;
      num1._threshold1 = _threshold1;
      num1._threshold2 = _threshold2;
      _value = temp;
   }
};


enum Status {
   LOW = 0,
   MEDIUM = 1,
   HIGH = 2,
};

Status getStatus(Number<int>& number)
{
   if (number.isLow()) {
      return LOW;
   } else if (number.isMedium()) {
      return MEDIUM;
   } else {
      assert(number.isHigh());
      return HIGH;
   }
}


void clusterSort(std::vector<Number<int>> &v)
{
   size_t l = v.size();
   int low = 0, high = l - 1, medium = -1;
   while (low < high) {
      Status status = getStatus(v[low]);
      if (status == LOW) {
         if (medium != -1) {
            v[medium].swap(v[low]);
            medium += 1;
            if (medium == low) {
               medium = -1;
            }
         }
         low += 1;
      } else if (status == HIGH) {
         v[high].swap(v[low]);
         high -= 1;
      } else {
         assert(status == MEDIUM);
         medium = (medium == -1) ? low : medium;
         low += 1;
      }
   }
}

int main(void)
{
   int a[]= {21, 5, 17, 12, 1, 2, 8, 9, 33, 18, 19, 30, 3};
   std::vector<Number<int>> v;
   for (unsigned int i = 0; i < sizeof(a) / sizeof(a[0]); i++) {
      Number<int> n(a[i], 10, 20);
      v.push_back(n);
   }
   clusterSort(v);
   for (auto i: v) {
      cout << i._value << endl;
   }
   return 0;
}
