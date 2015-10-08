#include <stdio.h>
#include <stdlib.h>

#define LEFT  0
#define RIGHT 1

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


int maxInBTree(struct BTNode *node)
{
   int maxLT, maxRT;
   if (node == NULL) {
      return 0;
   }
   maxLT = maxInBTree(node->nodes[LEFT]);
   maxRT = maxInBTree(node->nodes[RIGHT]);
   return maxLT > node->key ?
          (maxLT > maxRT ? maxLT : maxRT) :
          (node->key > maxRT ? node->key : maxRT);
}

struct BTNode* insert(struct BTNode* node, int key)
{
  if (node == NULL) {
    return newNode(key);
  } else {
    struct BTNode *temp;
    int f = rand() % 2 != 0;
    if (f) {
         temp = insert(node->nodes[LEFT], key);
         node->nodes[LEFT]  = temp;
    } else {
        temp = insert(node->nodes[RIGHT], key);
        node->nodes[RIGHT] = temp;
    }
    return node;
  }
}

void inordertrav(struct BTNode *node)
{
   if (node == NULL) {
      return;
   }
   inordertrav(node->nodes[LEFT]);
   printf("%d\n", node->key);
   inordertrav(node->nodes[RIGHT]);
}


int main(void)
{
  struct BTNode* root = NULL;
  int arr[] = {20, 8, 22, 4, 12, 10, 14, 45};

  for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
     root = insert(root, arr[i]);
  }
  inordertrav(root);
  printf("Max is %d\n", maxInBTree(root));

  return 0;
}
