class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = NULL, *tail = NULL;
        
        int carryOver = 0;
        while (l1 != NULL && l2 != NULL) {
            int tot = l1->val + l2->val + carryOver;
            ListNode *m = new ListNode(tot % 10);
            if (tail != NULL) {
                tail->next = m;
                tail = m;
            } else {
                head = tail = m;
            }
            carryOver = tot / 10;
            l1 = l1->next;
            l2 = l2->next;
        }
        while (l1 != NULL) {
            int tot = l1->val + carryOver;
            ListNode *m = new ListNode(tot % 10);
            if (tail != NULL) {
                tail->next = m;
                tail = m;
            } else {
                head = tail = m;
            }
            carryOver = tot / 10;
            l1 = l1->next;
        }
        while (l2 != NULL) {
            int tot = l2->val + carryOver;
            ListNode *m = new ListNode(tot % 10);
            if (tail != NULL) {
                tail->next = m;
                tail = m;
            } else {
                head = tail = m;
            }
            carryOver = tot / 10;
            l2 = l2->next;
        }
        if (carryOver != 0) {
            ListNode *m = new ListNode(carryOver);
            if (tail != NULL) {
                tail->next = m;
                tail = m;
            } else {
                head = tail = m;
            }
        }
        return head;
    }
};
