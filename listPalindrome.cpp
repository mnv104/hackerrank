#include <vector>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        struct ListNode *tmp1 = head, *tmp2 = NULL;
        int i = 0;
        int count = 0;
        vector<int> v;
        while (tmp1 != NULL) {
            tmp1 = tmp1->next;
            count++;
            i++;
            if ((i % 2) == 0) {
                if (tmp2 == NULL) {
                    tmp2 = head;
                } else {
                    tmp2 = tmp2->next;
                }
                v.push_back(tmp2->val);
            }
        }
        if (tmp2 == NULL) {
            return true;
        }
        if ((count % 2) != 0) {
           tmp2 = tmp2->next->next;
        } else {
           tmp2 = tmp2->next;
        }
        vector<int>::reverse_iterator it = v.rbegin();
        while (tmp2 != NULL) {
            if (it == v.rend()) {
                return false;
            }
            if (*it != tmp2->val) {
                return false;
            }
            tmp2 = tmp2->next;
            it++;
        }
        return true;
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
   int a1[] = {1, 3, 2, 5, 4, 3, 1};
   ListNode *n[1] = {NULL};
   n[0] = makeSortedList(a1, sizeof(a1)/sizeof(a1[0]));
   cout << "Input lists" << endl;
   displayList(n[0]);
   Solution s;
   cout << s.isPalindrome(n[0]) << endl;
   return 0;
}
 
