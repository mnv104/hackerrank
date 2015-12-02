#include <stdio.h>
#include <iostream>
#include <list>
#include <stdlib.h>

#define LEFT  0
#define RIGHT 1

using namespace std;

struct BTNode {
    int key;
    struct BTNode* nodes[2];
};


struct BTNode* newNode(int key)
{
  struct BTNode* node = (struct BTNode*) malloc(sizeof(*node));
  node->key   = key;
  node->nodes[LEFT] = NULL;
  node->nodes[RIGHT] = NULL;
  return node;
}


struct BTNode* insert(struct BTNode* node, int key)
{
  if (node == NULL) {
    return newNode(key);
  } else {
    struct BTNode *temp;
    if (key <= node->key) {
         temp = insert(node->nodes[LEFT], key);
         node->nodes[LEFT]  = temp;
    } else {
        temp = insert(node->nodes[RIGHT], key);
        node->nodes[RIGHT] = temp;
    }
    return node;
  }
}

struct ListNode {
   BTNode *btNode;
   int level;
   ListNode(BTNode *bt, int _level): btNode(bt), level(_level) { }
};

void levelordertrav(struct BTNode *node)
{
   if (node == NULL) {
      return;
   }
   std::list<ListNode *> l;
   int prevLevel = -1;
   l.push_back(new ListNode(node, 0));
   while (!l.empty()) {
      ListNode *f = l.front();
      if (f->btNode->nodes[LEFT] != NULL) {
         l.push_back(new ListNode(f->btNode->nodes[LEFT], f->level + 1));
      }
      if (f->btNode->nodes[RIGHT] != NULL) {
         l.push_back(new ListNode(f->btNode->nodes[RIGHT], f->level + 1));
      }
      if (prevLevel != -1 && prevLevel != f->level) {
         cout << endl;
      }
      cout << f->btNode->key << " ";
      prevLevel = f->level;
      l.pop_front();
   }
}


int main(void)
{
  struct BTNode* root = NULL;
  int arr[] = {20, 8, 22, 4, 12, 10, 14, 45};

  for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
     root = insert(root, arr[i]);
  }
  levelordertrav(root);

  return 0;
}
