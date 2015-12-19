#include <stdio.h>
#include <stdlib.h>

#define LEFT  0
#define RIGHT 1

struct BSTNode {
    int key;
    struct BSTNode* nodes[2];
};

struct BSTNode *
findLeftMostNode(struct BSTNode* node)
{
  struct BSTNode* tmp = node;
  while (tmp->nodes[LEFT] != NULL) {
    tmp = tmp->nodes[LEFT];
  }
  return tmp;
}

struct BSTNode *
findInOrderSuccessor(struct BSTNode *node, struct BSTNode **pSucc, int key)
{
   if (node == NULL) {
      return NULL;
   }
   if (node->key == key) {
      if (node->nodes[RIGHT] != NULL) {
         return findLeftMostNode(node->nodes[RIGHT]);
      } else {
         return *pSucc;
      }
   } else if (node->key > key) {
      pSucc = &node;
      return findInOrderSuccessor(node->nodes[LEFT], pSucc, key);
   } else {
      return findInOrderSuccessor(node->nodes[RIGHT], pSucc, key);
   }
}


struct BSTNode* newNode(int key)
{
  struct BSTNode* node = (struct BSTNode*) malloc(sizeof(*node));
  node->key   = key;
  node->nodes[LEFT] = NULL;
  node->nodes[RIGHT] = NULL;
  return node;
}

struct BSTNode* insert(struct BSTNode* node, int key)
{
  if (node == NULL) {
    return newNode(key);
  } else {
    struct BSTNode *temp;
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

int main(void)
{
  struct BSTNode* root = NULL;
  int arr[] = {20, 8, 22, 4, 12, 10, 14};

  for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
     root = insert(root, arr[i]);
  }
  for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
     struct BSTNode *succ, *next = NULL;
     succ = findInOrderSuccessor(root, &next, arr[i]);
     if (succ != NULL) {
      printf("In order successor of %d is %d\n", arr[i], succ->key);
     } else {
      printf("In order successor of key %d or key %d does not exist\n", arr[i], arr[i]);
     }
  }
  struct BSTNode *succ, *next = NULL;
  succ = findInOrderSuccessor(root, &next, 100);
  if (succ != NULL) {
     printf("In order successor of 100 is %d\n", succ->key);
  } else {
     printf("In order successor of 100 does not exist or key 100 does not exist!\n");
  }

  return 0;
}
