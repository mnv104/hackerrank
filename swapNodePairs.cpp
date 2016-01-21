/*
 * Given a linked list, swap every two adjacent nodes and return its head.
 *
 * For example,
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
 *
 * Your algorithm should use only constant space. You may not modify the values
 * in the list, only nodes itself can be changed.
 *
 */
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode *prevNode = NULL;
        ListNode *node = head;
        while (node != NULL && node->next != NULL) {
            ListNode *nextNode = node->next;
            ListNode *nextToNextNode = nextNode->next;
            nextNode->next = node;
            node->next = nextToNextNode;
            if (head == node) {
                head = nextNode;
            } else {
                prevNode->next = nextNode;
            }
            prevNode = node;
            node = nextToNextNode;
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
   head = s.swapPairs(head);
   h = head;
   while (h != NULL) {
      cout << h->val << " ";
      h = h->next;
   }
   cout << endl;
}
