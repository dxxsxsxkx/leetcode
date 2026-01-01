class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;

        ListNode* node_curr = &dummy;
        ListNode* runner = head;

        while (runner != nullptr && runner->next != nullptr){
            if (runner->val == runner->next->val) {
                // flag
                int val_dup = runner->val;
                
                // ensures runner is past the duplicated block
                while (runner->val == val_dup) {
                    runner = runner->next;
                }

                node_curr->next = runner;
                
            } else {
                // detach node_curr from dummy.next
                node_curr = runner;
                runner = runner->next;
            }
        }

        return dummy.next;
    }
};