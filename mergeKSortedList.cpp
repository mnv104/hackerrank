#include <vector>
#include <limits.h>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    ListNode *findMin(vector<ListNode *> &lists) {
        size_t l = lists.size();
        ListNode *min = NULL;
        int minVal = INT_MAX;
        int vecPos;
        if (l == 0) {
            return NULL;
        }
        for (unsigned int i = 0; i < l; i++) {
            if (lists[i] != NULL && lists[i]->val < minVal) {
                min = lists[i];
                minVal = lists[i]->val;
                vecPos = i;
            }
        }
        if (min != NULL) {
            lists[vecPos] = min->next;
        }
        return min;
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *head = NULL, *node = NULL;
        ListNode *min;
        while ((min = findMin(lists)) != NULL) {
            if (node == NULL) {
                head = node = min;
            } else {
                node->next = min;
                node = node->next;
            }
        }
        return head;
    }
};

ListNode* makeSortedList(int *a, int number)
{
   ListNode *node = NULL, *head = NULL;
   for (int i = 0; i < number; i++) {
      if (node == NULL) {
         head = node = new ListNode(a[i]);
      } else {
         node->next = new ListNode(a[i]);
         node = node->next;
      }
   }
   return head;
}

void displayList(ListNode *h)
{
   ListNode *tmp = h;
   while (tmp != NULL) {
      cout << tmp->val << " ";
      tmp = tmp->next;
   }
   cout << endl;
   return;
}

int main()
{
   int a1[] = {3, 4, 6, 9, 10, 15, 20};
   int a2[] = {-4, -2, 0, 1, 3, 8, 10, 11, 17, 22};
   int a3[] = {-10, -8, -4, 20, 29, 34};
   int a4[] = {-100, -40, -20, -10, 1, 2, 39};
   ListNode *n[4] = {NULL, NULL, NULL, NULL};
   n[0] = makeSortedList(a1, sizeof(a1)/sizeof(a1[0]));
   n[1] = makeSortedList(a2, sizeof(a2)/sizeof(a2[0]));
   n[2] = makeSortedList(a3, sizeof(a3)/sizeof(a3[0]));
   n[3] = makeSortedList(a4, sizeof(a4)/sizeof(a4[0]));
   cout << "Input lists" << endl;
   displayList(n[0]);
   displayList(n[1]);
   displayList(n[2]);
   displayList(n[3]);
   vector<ListNode *> v;
   v.push_back(n[0]);
   v.push_back(n[1]);
   v.push_back(n[2]);
   v.push_back(n[3]);
   Solution s;
   ListNode *h;
   h = s.mergeKLists(v);
   cout << "Merged lists" << endl;
   displayList(h);
}
