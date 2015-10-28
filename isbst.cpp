#include <vector>
#include <limits.h>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct TreeNode* insertBST(struct TreeNode* node, int key)
{
  if (node == NULL) {
    return new TreeNode(key);
  } else {
    struct TreeNode *temp;
    if (key <= node->val) {
         temp = insertBST(node->left, key);
         node->left = temp;
    } else {
        temp = insertBST(node->right, key);
        node->right = temp;
    }
    return node;
  }
}

struct TreeNode* insertBT(struct TreeNode* node, int key, bool left)
{
  if (node == NULL) {
    return new TreeNode(key);
  } else {
    struct TreeNode *temp;
    if (left) {
         temp = insertBT(node->left, key, left);
         node->left = temp;
    } else {
        temp = insertBT(node->right, key, left);
        node->right = temp;
    }
    return node;
  }
}



class Solution {
public:
    bool isValidBSTInt(TreeNode *node, long minVal, long maxVal) {
        if (node == NULL) {
            return true;
        }
        return (node->val > minVal &&
                node->val < maxVal &&
                isValidBSTInt(node->left, minVal, node->val) &&
                isValidBSTInt(node->right, node->val, maxVal));
    }
    bool isValidBST(TreeNode* root) {
        return isValidBSTInt(root, LONG_MIN, LONG_MAX);
    }
};

int func(void)
{
  struct TreeNode* root = NULL;
  int arr[] = {20, 8, 22, 4, 12, 10, 14, 45};

  for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
     root = insertBST(root, arr[i]);
  }
  Solution s;
  cout << s.isValidBST(root) << endl;
  return 0;
}

int func2(void)
{
  struct TreeNode* root = NULL;
  int arr[] = {0, -1};

  for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
     root = insertBST(root, arr[i]);
  }
  Solution s;
  cout << s.isValidBST(root) << endl;
  return 0;
}


int func3(void)
{
  struct TreeNode* root = NULL;
  int arr[] = {20, 8, 22, 4, 12, 10, 14, 45};

  for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
     root = insertBT(root, arr[i], (i % 3) != 0);
  }
  Solution s;
  cout << s.isValidBST(root) << endl;
  return 0;
}


int main(void)
{
   func();
   func2();
   func3();
   return 0;
}
