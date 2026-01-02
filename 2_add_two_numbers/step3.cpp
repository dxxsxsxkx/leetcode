class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(-1000);
        ListNode* node_current = &dummy;

        int carry = 0;

        while (l1 || l2 || carry != 0) {
            int sum = carry; 

            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }

            carry = sum / 10;
            int first_digit = sum % 10;

            node_current->next = new ListNode(first_digit);
            node_current = node_current->next;

        }

        return dummy.next;
    }
};