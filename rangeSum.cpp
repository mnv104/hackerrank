#include <vector>
#include <stdexcept>
#include <list>
#include <iostream>

using namespace std;
class NumArray {
public:
    vector<int> _nums;
    NumArray(vector<int> &nums) : _nums(nums) {
    }
    virtual void update(int i, int val) = 0;
    virtual int sumRange(int i, int j) = 0;
};

class NumArrayLinear: public NumArray {
private:
    vector<int> cumSum;
public:
    NumArrayLinear(vector<int> &nums): NumArray(nums) {
        cumSum.resize(nums.size());
        int total = 0;
        for (unsigned int j = 0; j < _nums.size(); j++) {
            total += nums[j];
            cumSum[j] = total;
        }
    }
    void update(int i, int val) override {
       int diff = (val - _nums[i]);
       _nums[i] = val;
       for (unsigned int j = i; j < _nums.size(); j++) {
          if (j == 0) {
             cumSum[j] = val;
          } else {
            cumSum[j] += diff;
          }
       }
    }
    int sumRange(int i, int j) override {
       return cumSum[j] - cumSum[i] + _nums[i];
    }
};


class NumArrayLog: public NumArray {
private:
   struct ArrayNode {
      int sum;
      int lIndex;
      int rIndex;
      ArrayNode *left;
      ArrayNode *right;
      ArrayNode() { }
      ArrayNode(int _sum, int _lIndex, int _rIndex): sum(_sum),
         lIndex(_lIndex), rIndex(_rIndex), left(nullptr), right(nullptr) { }
   };
   vector<ArrayNode *> v;
   ArrayNode *root;
   ArrayNode *buildTree(const vector<ArrayNode *> &v, int startIndex, int endIndex) {
      if (startIndex == endIndex) {
         return v[startIndex];
      }
      if (startIndex + 1 == endIndex) {
         ArrayNode *node = new ArrayNode(v[startIndex]->sum + v[endIndex]->sum,
                              startIndex, endIndex);
         node->left = v[startIndex];
         node->right = v[endIndex];
         return node;
      }
      int middleIndex = (startIndex + endIndex) / 2;
      ArrayNode *node = new ArrayNode;
      node->left = buildTree(v, startIndex, middleIndex);
      node->right = buildTree(v, middleIndex + 1, endIndex);
      node->sum = node->left->sum + node->right->sum;
      node->lIndex = node->left->lIndex;
      node->rIndex = node->right->rIndex;
      return node;
   }

public:
   NumArrayLog(vector<int> &nums): NumArray(nums), root(nullptr) {
      for (unsigned int i = 0; i < _nums.size(); i++) {
         ArrayNode *n = new ArrayNode(_nums[i], i, i);
         v.push_back(n);
      }
      root = buildTree(v, 0, _nums.size() - 1);
   }
   ~NumArrayLog() {
      vector<ArrayNode *>::iterator it = v.begin();
      while (it != v.end()) {
         ArrayNode *n = *it;
         it = v.erase(it);
         delete n;
      }
   }
   void display() {
      ArrayNode *n = root;
      std::list<ArrayNode *> l;
      l.push_back(n);
      while (!l.empty()) {
         ArrayNode *n = l.front();
         l.pop_front();
         cout << "Sum " << n->sum << "( " << n->lIndex << " - " << n->rIndex << " ) " << endl;
         if (n->left != nullptr) {
            l.push_back(n->left);
         }
         if (n->right != nullptr) {
            l.push_back(n->right);
         }
      }
   }

   void updateInt(ArrayNode *node, int i, int diff) {
      if (node == nullptr) {
         return;
      }
      if (node->rIndex < i || node->lIndex > i) {
         return;
      }
      if (node->lIndex <= i && node->rIndex >= i) {
         node->sum += diff;
      }
      updateInt(node->left, i, diff);
      updateInt(node->right, i, diff);
   }

   void update(int i, int val) override {
      ArrayNode *n = root;
      if (n == nullptr) {
         throw std::runtime_error("Invalid root");
      }
      int diff = val - _nums[i];
      _nums[i] = val;
      updateInt(n, i, diff);
   }

   int sumRangeInt(ArrayNode *node, int i, int j) {
      if (node == nullptr) {
         return 0;
      }
      if (node->lIndex >= i && node->rIndex <= j) {
         return node->sum;
      }
      if (j < node->lIndex || i > node->rIndex) {
         return 0;
      }
      return sumRangeInt(node->left, i, j) +
         sumRangeInt(node->right, i, j);
   }

   int sumRange(int i, int j) override {
      ArrayNode *n = root;
      if (n == nullptr) {
         throw std::runtime_error("Invalid root");
      }
      return sumRangeInt(n, i, j);
   }
};


int func1()
{
   int a[] = {1, 3, 5};
   vector<int> nums(a, a+sizeof(a)/sizeof(a[0]));
   NumArrayLinear numArray1(nums);
   cout << "Linear implementation " << endl;
   for (unsigned int i = 0; i < nums.size(); i++) {
      for (unsigned int j = i; j < nums.size(); j++) {
         cout << "[ " << i << " - " << j << " ] -> " <<
            numArray1.sumRange(i, j) << endl;
      }
   }
   numArray1.update(1, 2);
   cout << "After update " << endl;
   cout << "Linear implementation " << endl;
   for (unsigned int i = 0; i < nums.size(); i++) {
      for (unsigned int j = i; j < nums.size(); j++) {
         cout << "[ " << i << " - " << j << " ] -> " <<
            numArray1.sumRange(i, j) << endl;
      }
   }

   NumArrayLog numArray2(nums);
   cout << "Log implementation " << endl;
   for (unsigned int i = 0; i < nums.size(); i++) {
      for (unsigned int j = i; j < nums.size(); j++) {
         cout << "[ " << i << " - " << j << " ] -> " <<
            numArray2.sumRange(i, j) << endl;
      }
   }
   numArray2.update(1, 2);
   cout << "After update " << endl;
   cout << "Log implementation " << endl;
   for (unsigned int i = 0; i < nums.size(); i++) {
      for (unsigned int j = i; j < nums.size(); j++) {
         cout << "[ " << i << " - " << j << " ] -> " <<
            numArray2.sumRange(i, j) << endl;
      }
   }



   return 0;
}

int main()
{
   func1();
   return 0;
}
