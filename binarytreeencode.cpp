#include <vector>
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

void inordertrav(struct TreeNode *node)
{
   if (node == NULL) {
      return;
   }
   inordertrav(node->left);
   printf("%d\n", node->val);
   inordertrav(node->right);
}


struct d {
   TreeNode *n;
   int depth;
   d(TreeNode *n1, int depth1) : n(n1), depth(depth1) { }
};

void bfs(struct TreeNode *node)
{
   vector<d *> v;
   if (node == NULL) {
      return;
   }
   v.push_back(new d(node, 0));
   while (v.size() > 0) {
      struct d *n = v.front();
      v.erase(v.begin());
      if (n->n != NULL) {
         printf("[%d] %d\n", n->depth, n->n->val);
         v.push_back(new d(n->n->left, n->depth + 1));
         v.push_back(new d(n->n->right, n->depth + 1));
      }
   }
}

class Codec {
public:
    void serializeInt(std::vector<TreeNode *> &v, string &encodedBuffer) {
        while (v.size() > 0) {
           TreeNode *node = v.front();
           v.erase(v.begin());
           if (node == NULL) {
              encodedBuffer += "null ";
           } else {
              std::stringstream ss;
              ss << node->val;
              encodedBuffer += ss.str();
              encodedBuffer += ' ';
              v.push_back(node->left);
              v.push_back(node->right);
           }
        }
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string encodedBuffer;
        vector<TreeNode *> v;
        v.push_back(root);
        encodedBuffer += "[";
        serializeInt(v, encodedBuffer);
        encodedBuffer += "]";
        return encodedBuffer;
    }

    TreeNode * deserializeInt(string &decodedBuffer) {
        string token;
        stringstream ss(decodedBuffer);
        std::vector<TreeNode *> v;
        int count = 0;
        TreeNode *root = NULL;

        while (ss >> token) {
            if (token != "null") {
                std::string::size_type sz;
                int t = stoi(token, &sz);
                TreeNode *node = new TreeNode(t);
                v.push_back(node);
                if (count != 0) {
                    TreeNode *parent = v.front();
                    if ((count % 2) == 0) {
                        parent->right = node;
                    } else {
                        parent->left = node;
                    }
                } else {
                   root = node;
                }
            }
            if (count != 0 && ((count % 2) == 0)) {
               v.erase(v.begin());
            }
            count += 1;
        }
        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.length() == 0) {
            throw std::invalid_argument("Invalid encoded string");
        }
        if (data[0] != '[' || data[data.length() - 1] != ']') {
            throw std::invalid_argument("Invalid encoded string without braces");
        }
        string d = data.substr(1, data.length() - 2);
        return deserializeInt(d);
    }
};

int func(void)
{
  struct TreeNode* root = NULL;
  int arr[] = {20, 8, 22, 4, 12, 10, 14, 45};

  for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
     root = insertBST(root, arr[i]);
  }
  inordertrav(root);
  Codec codec;
  cout << codec.serialize(root) << endl;
  struct TreeNode *newRoot;
  newRoot = codec.deserialize(codec.serialize(root));
  inordertrav(newRoot);
  return 0;
}

int func2(void)
{
  struct TreeNode* root = NULL;
  int arr[] = {5, 2, 3, 10, 4, 8, 1};

  for (unsigned int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
     root = insertBT(root, arr[i], (i % 2) == 0);
  }
  bfs(root);
  Codec codec;
  cout << codec.serialize(root) << endl;
  struct TreeNode *newRoot;
  newRoot = codec.deserialize(codec.serialize(root));
  bfs(newRoot);
  return 0;
}

int main(void)
{
   func();
   func2();
   return 0;
}
