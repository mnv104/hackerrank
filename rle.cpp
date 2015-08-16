#include <sstream>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <string>


template <typename T>
class RLEClass {
public:
   T _val;
   bool _init;
   uint32_t _count;
public:
   RLEClass(): _init(false), _count(0) { }
   ~RLEClass() = default;
   void operator=(const T& val) { _val = val; _count = 1; _init = true;}
   bool operator==(const T& val) {
      if (!_init) {
         return false;
      }
      return _val == val;
   }
   void increment() {
      if (!_init) {
         throw std::runtime_error("Uninitialized init character");
      }
      _count++;
   }
};


typedef RLEClass<char> initChar;

std::ostream &operator<<(std::ostream &s, initChar ch)
{
   if (!ch._init) {
      return s;
   }
   return s << ch._val << ch._count;
}


std::string RLEEncode(const std::string &s)
{
   std::stringstream ss;
   size_t l = s.length();
   if (l == 0) {
      throw std::invalid_argument("Invalid string");
   }
   initChar ch;

   for (int i = 0;i < l; i++) {
      if (ch == s[i]) {
         ch.increment();
      } else {
         ss << ch;
         ch = s[i];
      }
   }
   ss << ch;
   return ss.str();
}

int main(int argc, const char *argv[])
{
   std::string s;
   if (argc > 1) {
      s = std::string(argv[1]);
   }
   try {
      std::string r = RLEEncode(s);
      std::cout << "Run length encoded string: " << r << std::endl;
   } catch (const std::exception &e) {
      std::cout << "Failed: " << e.what() << std::endl;
   }
   return 0;
}
