/*
 * Given a linked list, reverse the nodes of a linked list k at a time and
 * return its modified list.
 *
 * If the number of nodes is not a multiple of k then left-out nodes in the end
 * should remain as it is.
 *
 * You may not alter the values in the nodes, only nodes itself may be changed.
 *
 * Only constant memory is allowed.
 *
 * For example,
 * Given this linked list: 1->2->3->4->5
 *
 * For k = 2, you should return: 2->1->4->3->5
 *
 * For k = 3, you should return: 3->2->1->4->5
 *
 */
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
       ListNode *node = head;
       ListNode *prevNode = NULL;
       if (k == 1) {
          return head;
       }
       while (node != NULL) {
          ListNode *v[k];
          int count = 0;
          ListNode *tmp = node;
          while (tmp != NULL && count < k) {
             v[count++] = tmp;
             tmp = tmp->next;
          }

          if (count != k) {
             break;
          }
          v[0]->next = v[k-1]->next;
          for (int i = k-1; i > 0; i--) {
             v[i]->next = v[i-1];
          }
          if (head == v[0]) {
             head = v[k-1];
          } else {
             prevNode->next = v[k-1];
          }
          prevNode = v[0];
          node = v[0]->next;
       }
       return head;
    }
};
 

int main()
{
   int a[] = {2, 5, 3, 4, 6, 2, 2};
   ListNode *head = NULL, *tail = NULL;
   for (unsigned int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
      ListNode *node = new ListNode(a[i]);
      if (head == NULL) {
         head = tail = node;
      } else {
         tail->next = node;
         tail = node;
      }
   }
   ListNode *h = head;
   while (h != NULL) {
      cout << h->val << " ";
      h = h->next;
   }
   cout << endl;
   Solution s;
   head = s.reverseKGroup(head, 3);
   h = head;
   while (h != NULL) {
      cout << h->val << " ";
      h = h->next;
   }
   cout << endl;
   return 0;
}
