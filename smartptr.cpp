#include <iostream>
using namespace std;

template <typename T>
class smartptr {
private:
   int _refCount;
   T *_p;
public:
   smartptr() : _refCount(0), _p(nullptr) {
   }
   smartptr(T *p): _p(p), _refCount(1) {
   }
   smartptr(smartptr &s) {
      _refCount = s.getRefCount();
      _p = s.getPtr();
   }
   smartptr(smartptr&& s) {
      _refCount = s.getRefCount();
      _p = s.getPtr();
      s.setRefCount(0);
      s.setPtr(nullptr);
   }
   ~smartptr() {
      _refCount--;
      if (_refCount == 0) {
         delete _p;
      }
   }
   smartptr &operator=(smartptr &&s) {
      if (_refCount > 0) {
         _refCount--;
         if (_refCount == 0) {
            delete _p;
         }
      }
      _refCount = s.getRefCount();
      _p = s.getPtr();
      s.setRefCount(0);
      s.setPtr(nullptr);
      return *this;
   }
   int getRefCount() {
      return _refCount;
   }
   T *getPtr() {
      return _p;
   }
   void setRefCount(int r) {
      _refCount = r;
   }
   void setPtr(T *p) {
      _p = p;
   }
   T operator*() {
      return *_p;
   }
   T *operator->() const {
      return _p;
   }
};


class TestClass {
public:
   int v;
   int *q;
   TestClass(int _v): v(_v) {
      if (_v > 0) {
         q = new int[_v];
      } else {
         q = nullptr;
      }
   }
   ~TestClass() {
      if (q) {
         cout << "Freeing! " << endl;
         delete [] q;
      }
   }
};

template <class T, class... Args>
smartptr<T> makeSmartPtr(Args&&... args)
{
   return smartptr<T>(new T(std::forward<Args>(args)...));
}

void func(const smartptr<TestClass> &s)
{
   cout << s->v << endl;
}

int main()
{
   smartptr<TestClass> s = makeSmartPtr<TestClass>(5);
   func(s);
}
