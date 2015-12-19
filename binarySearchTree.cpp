#include <iostream>
#include <list>
#include <deque>
#include <stack>
#include <assert.h>
#include <exception>

using namespace std;

template <typename T>
class BinarySearchTree {
public:
   struct BSTNode {
      T val;
      BSTNode *left, *right;
      BSTNode(T _val) : val(_val), left(nullptr), right(nullptr) { }
   };
   struct BSTException : public std::exception {
      std::string _err;
      BSTException(const std::string &err) : _err(err) { }
   };
private:
   BSTNode *root;
public:

   ~BinarySearchTree() {
      std::list<BSTNode *> l;
      if (root == NULL) {
         return;
      }
      l.push_back(root);
      while (!l.empty()) {
         BSTNode *node = l.front();
         l.pop_front();
         if (node->left) {
            l.push_back(node->left);
         }
         if (node->right) {
            l.push_back(node->right);
         }
         delete node;
      }
   }
   enum TravOrder {
      BST_INORDER,
      BST_PREORDER,
      BST_POSTORDER,
   };

private:
   class iteratorInt {
      BinarySearchTree<T> *tree;
      TravOrder order;
   public:
      BinarySearchTree<T> *getTree() const {
         return tree;
      }
      TravOrder getOrder() const {
         return order;
      }
      virtual size_t size() const {
         cerr << "size unimplemented " << endl;
         throw BSTException("Unimplemented");
      }
      virtual T getCurrent() {
         cerr << "getCurrent unimplemented " << endl;
         throw BSTException("Unimplemented");
      }
      virtual iteratorInt setNext() {
         cerr << "setNext unimplemented " << endl;
         throw BSTException("Unimplemented");
      }
      virtual bool isNotEqual(const iteratorInt &a) {
         cerr << "Is not equal unimplemented " << endl;
         throw BSTException("Unimplemented");
      }
      iteratorInt(BinarySearchTree<T> *_tree, TravOrder _order) :
         order(_order), tree(_tree) { }
      virtual ~iteratorInt() { }
      T operator*() {
         return getCurrent();
      }
      virtual iteratorInt operator++() {
         return setNext();
      }
      virtual iteratorInt operator++(int unused) {
         return setNext();
      }
      bool operator!=(const iteratorInt &a) {
         bool ret = isNotEqual(a);
         return ret;
      }
   };

   class inOrderIterator: public iteratorInt {
   private:
      std::stack<BSTNode *> v;
      BSTNode *_node;
   public:
      inOrderIterator(BinarySearchTree<T> *tree) :
         iteratorInt(tree, BST_INORDER), _node(nullptr) {
         if (tree != nullptr) {
            BSTNode *node = tree->root;
            while (node != nullptr) {
               //cout << "Pushing "<< node->val << endl;
               v.push(node);
               node = node->left;
            }
         }
      }
      size_t size() const override {
         return v.size();
      }

      T getCurrent() override {
         if (_node == nullptr) {
            BSTNode *node = v.top();
            _node = node;
            //cout << "Popping "<< _node->val << endl;
            v.pop();
            if (node->right) {
               BSTNode *tmp = node->right;
               while (tmp != nullptr) {
                  v.push(tmp);
                  //cout << "Pushing "<< tmp->val << endl;
                  tmp = tmp->left;
               }
            }
         }
         return _node->val;
      }
      
      iteratorInt setNext() override
      {
         _node = nullptr;
         return *this;
      }

      virtual bool isNotEqual(const iteratorInt &a) override {
         bool ret = v.size() != a.size();
         return ret;
      }
   };

   class preOrderIterator : public iteratorInt {
   private:
      std::deque<BSTNode *> v;
      BSTNode *_node;
   public:
      preOrderIterator(BinarySearchTree<T> *tree) :
         iteratorInt(tree, BST_PREORDER), _node(nullptr) {
         if (tree != nullptr) {
            BSTNode *node = tree->root;
            //cout << "Pushing "<< node->val << endl;
            v.push_back(node);
         }
      }
      size_t size() const override {
         return v.size();
      }

      T getCurrent() override {
         if (_node == nullptr) {
            BSTNode *node = v.front();
            _node = node;
            //cout << "Popping "<< _node->val << endl;
            v.pop_front();
            if (node->right) {
               v.push_front(node->right);
               //cout << "Pushing "<< node->right->val << endl;
            }
            if (node->left) {
               v.push_front(node->left);
               //cout << "Pushing "<< node->left->val << endl;
            }
         }
         return _node->val;
      }
      
      iteratorInt setNext() override
      {
         _node = nullptr;
         return *this;
      }

      virtual bool isNotEqual(const iteratorInt &a) override {
         return v.size() != a.size();
      }
   };

   class postOrderIterator : public iteratorInt {
   private:
      struct DequeNode {
         BSTNode *node;
         bool descendNode;
         DequeNode(BSTNode *_node): node(_node), descendNode(true) { }
      };

      std::deque<DequeNode> v;
      BSTNode *_node;
   public:
      postOrderIterator(BinarySearchTree<T> *tree) :
         iteratorInt(tree, BST_POSTORDER), _node(nullptr) {
         if (tree != nullptr) {
            BSTNode *node = tree->root;
            //cout << "Pushing "<< node->val << endl;
            v.push_front(DequeNode(node));
         }
      }
      size_t size() const override {
         return v.size();
      }

      T getCurrent() override {
         if (_node == nullptr) {
            while (1) {
               DequeNode &dNode = v.front();
               BSTNode *node = dNode.node;
               if (dNode.descendNode == false ||
                   (!node->right && !node->left)) {
                  _node = node;
                  //cout << "Popping "<< _node->val << endl;
                  v.pop_front();
                  break;
               } else {
                  if (node->right) {
                     v.push_front(DequeNode(node->right));
                     //cout << "Pushing "<< node->right->val << endl;
                  }
                  if (node->left) {
                     v.push_front(DequeNode(node->left));
                     //cout << "Pushing "<< node->left->val << endl;
                  }
                  dNode.descendNode = false;
               }
            }
         }
         return _node->val;
      }
      
      iteratorInt setNext() override
      {
         _node = nullptr;
         return *this;
      }

      virtual bool isNotEqual(const iteratorInt &a) override {
         return v.size() != a.size();
      }

   };

public:
   class iterator {
   public:
      iteratorInt *it;
      iterator(BinarySearchTree<T> *tree, TravOrder order) {
         if (order == BST_INORDER) {
            it = new inOrderIterator(tree);
         } else if (order == BST_PREORDER) {
            it = new preOrderIterator(tree);
         } else if (order == BST_POSTORDER) {
            it = new postOrderIterator(tree);
         } else  {
            assert(0);
         }
      }
      iterator(const iterator &a) {
         if (a.it->getOrder() == BST_INORDER) {
            it = new inOrderIterator(a.it->getTree());
         } else if (a.it->getOrder() == BST_PREORDER) {
            it = new preOrderIterator(a.it->getTree());
         } else if (a.it->getOrder() == BST_POSTORDER) {
            it = new postOrderIterator(a.it->getTree());
         } else  {
            assert(0);
         }
      }

      ~iterator() {
         delete it;
      }

      T operator*() {
         return it->getCurrent();
      }
      iterator operator++() {
         it->setNext();
         return *this;
      }
      iterator operator++(int unused) {
         it->setNext();
         return *this;
      }
      bool operator!=(const iterator &a) {
         return *it != *(a.it);
      }

   };

private:
   void display(ostream &o, const std::string &s, TravOrder order) {
      BinarySearchTree<int>::iterator it = begin(order), itEnd = end(order);
      o << s << " : ";
      while (it != itEnd) {
         o << (*it) << " ";
         it++;
      }
      o << endl;
   }


public:
   iterator begin(TravOrder order) {
      return iterator(this, order);
   }

   iterator end(TravOrder order) {
      return iterator(nullptr, order);
   }

   BinarySearchTree() : root(nullptr) { }
   void insert(T item);

   void displayInOrder(ostream &o, const std::string &s)
   {
      display(o, "In-Order " + s, BinarySearchTree<int>::BST_INORDER);
   }

   void displayPreOrder(ostream &o, const std::string &s)
   {
      display(o, "Pre-Order " + s, BinarySearchTree<int>::BST_PREORDER);
   }

   void displayPostOrder(ostream &o, const std::string &s)
   {
      display(o, "Post-Order " + s, BinarySearchTree<int>::BST_POSTORDER);
   }

   void remove(T item);
};


template <typename T>
void BinarySearchTree<T>::insert(T item)
{
   BSTNode *node = root, *prevNode = nullptr;
   bool left;
   while (node != nullptr) {
      if (node->val == item) {
         throw BSTException("Duplicate item being inserted");
      } else if (node->val < item) {
         prevNode = node;
         node = node->right;
         left = false;
      } else {
         prevNode = node;
         node = node->left;
         left = true;
      }
   }
   if (prevNode == nullptr) {
      root = new BSTNode(item);
   } else {
      if (left) {
         assert(prevNode->left == nullptr);
         prevNode->left = new BSTNode(item);
      } else {
         assert(prevNode->right == nullptr);
         prevNode->right = new BSTNode(item);
      }
   }
}

int func1()
{
   BinarySearchTree<int> bst1;
   int arr[] = {20, 8, 22, 4, 12, 10, 14};

   for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
      bst1.insert(arr[i]);
   }
   bst1.displayInOrder(cout, "Test1");
   bst1.displayPreOrder(cout, "Test1");
   bst1.displayPostOrder(cout, "Test1");
   return 0;
}

int func2()
{
   BinarySearchTree<int> bst1;
   int arr[] = {20, 10, 25, 18, 7, 15, 23, 21, 24};

   for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
      bst1.insert(arr[i]);
   }
   bst1.displayInOrder(cout, "Test2");
   bst1.displayPreOrder(cout, "Test2");
   bst1.displayPostOrder(cout, "Test2");
   return 0;
}

int func3()
{
   BinarySearchTree<int> bst1;
   int arr[] = {20, 20};
   for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
      bst1.insert(arr[i]);
   }
   return 0;
}


int main()
{
   func1();
   func2();
   try {
      func3();
      cerr << "Test3 did not throw exception" << endl;
      exit(1);
   } catch (...) {
      cout << "Test3 did throw exception" << endl;
   }
   return 0;
}
