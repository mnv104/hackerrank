/*
 * Given a linked list, remove the nth node from the end of list and return its
 * head.
 *
 * For example,
 *
 *    Given linked list: 1->2->3->4->5, and n = 2.
 *
 *       After removing the second node from the end, the linked list becomes
 *       1->2->3->5.
 *       Note:
 *       Given n will always be valid.
 *       Try to do this in one pass.
 */

#include <iostream>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};



class Solution {
public:
       ListNode* removeNthFromEnd(ListNode* head, int n) {
          std::stack<ListNode *> s;
          ListNode *node = head;
          while (node != NULL) {
             s.push(node);
             node = node->next;
          }
          while (n > 1) {
             s.pop();
             n--;
          }
          ListNode *nodeToBeDeleted = s.top();
          s.pop();
          ListNode *prevNode;
          if (s.size() == 0) {
             prevNode = NULL;
          } else {
             prevNode = s.top();
          }
          if (prevNode != NULL) {
             prevNode->next = nodeToBeDeleted->next;
          } else {
             head = nodeToBeDeleted->next;
          }
          return head;
       }
};

int main()
{
   //int a[] = {2, 5, 3, 4, 6, 2, 2};
   int a[] = {1};
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
   head = s.removeNthFromEnd(head, 1);
   h = head;
   while (h != NULL) {
      cout << h->val << " ";
      h = h->next;
   }
   cout << endl;
   return 0;
}
 
